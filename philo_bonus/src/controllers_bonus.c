/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:33:36 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/26 23:31:18 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	threads_error_handler(int status, t_action action)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_handler(THD_MEM, true, NULL);
	else if (status == EPERM)
		error_handler(THD_PERM, true, NULL);
	else if (status == EINVAL && action == CREATE)
		error_handler(THD_INV, true, NULL);
	else if (status == EINVAL && (action == JOIN || action == DETACH))
		error_handler(THD_JOIN, true, NULL);
	else if (status == ESRCH)
		error_handler(THD_ID, true, NULL);
	else if (status == EDEADLK)
		error_handler(THD_DEAD, true, NULL);
}

void	threads_controller(pthread_t *thread, void *(*function)(void *),
							void *args, t_action action)
{
	if (action == CREATE)
		threads_error_handler(pthread_create(thread, NULL, function, args),
			action);
	else if (action == JOIN)
		threads_error_handler(pthread_join(*thread, NULL), action);
	else if (action == DETACH)
		threads_error_handler(pthread_detach(*thread), action);
	else
		error_handler(INVALID_TACTION, true, NULL);
}

static void	sem_error_handler(int error_code, t_data *data)
{
	if (error_code == 0)
		return ;
	if (error_code == -1 || error_code == *SEM_FAILED)
		error_code = errno;
	else
		return ;
	if (error_code == EINVAL)
		error_handler(SEM_AINV, true, data);
	else if (error_code == EACCES)
		error_handler(SEM_ACC, true, data);
	else if (error_code == EINTR)
		error_handler(SEM_INTR, true, data);
	else if (error_code == ENAMETOOLONG)
		error_handler(SEM_TLONG, true, data);
	else if (error_code == ENFILE)
		error_handler(SEM_NFILE, true, data);
	else if (error_code == ENOENT)
		error_handler(SEM_NENT, true, data);
	else if (error_code == ENOSPC)
		error_handler(SEM_NSPC, true, data);
	else if (error_code == EDEADLK)
		error_handler(SEM_DEAD, true, data);
}

void	sem_controller(t_sem *s_data, t_action act, size_t size, t_data *data)
{
	if (act == OPEN)
	{
		s_data->sem = sem_open(s_data->path, O_CREAT, 0644, size);
		if (s_data->sem == SEM_FAILED)
			sem_error_handler(*s_data->sem, data);
		s_data->init = true;
	}
	else if (act == WAIT)
		sem_error_handler(sem_wait(s_data->sem), data);
	else if (act == POST)
		sem_error_handler(sem_post(s_data->sem), data);
	else if (act == CLOSE)
		sem_error_handler(sem_close(s_data->sem), data);
	else if (act == UNLINK)
		sem_error_handler(sem_unlink(s_data->path), data);
	else
		error_handler(INVALID_SACTION, true, data);
	if (act == CLOSE || act == UNLINK)
		s_data->init = false;
}

void	process_controller(t_philo *philo, void (*function)(t_philo *))
{
	philo->pid = fork();
	if (philo->pid == -1)
		error_handler(FORK_FAIL, true, philo->data);
	if (philo->pid == 0)
	{
		sem_controller(&philo->data->s_dinner_starts, WAIT, 0, philo->data);
		philo->data->start_time = get_time(MILLISECONDS, philo->data);
		philo->last_meal_time = philo->data->start_time;
		threads_controller(&philo->data->philo_supervisor_id, philo_supervisor, philo,
			CREATE);
		threads_controller(&philo->data->philo_supervisor_id, NULL, NULL, DETACH);
		function(philo);
		free_sems(philo->data);
		free(philo);
		exit(EXIT_SUCCESS);
	}
}
