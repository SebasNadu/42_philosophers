/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:33:36 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/24 11:33:52 by sebasnadu        ###   ########.fr       */
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

static void	sem_error_handler(sem_t status, t_action action, t_data *data)
{
	if (status == 0)
		return ;
	else if (status == EINVAL)
		error_handler(SEM_AINV, true, data);
	else if (status == EACCESS)
		error_handler(SEM_ACC, true, data);
	else if (status == EINTR)
		error_handler(SEM_INTR, true, data);
	else if (status == ENAMETOOLONG)
		error_handler(SEM_TLONG, true, data);
	else if (status == ENFILE)
		error_handler(SEM_NFILE, true, data);
	else if (status == ENOENT)
		error_handler(SEM_NENT, true, data);
	else if (status == ENOSPC)
		error_handler(SEM_NSPC, true, data);
	else if (status == EDEADLK)
		error_handler(SEM_DEAD, true, data);
}

void	sem_controller(t_sem *s_data, t_action act, size_t size, t_data *data)
{
	if (act == OPEN)
	{
		s_data->sem = sem_open(s_data->path, O_CREAT, 0644, size);
		if (s_data->sem != SEM_FAILED)
			s_data->init = true;
	}
	else if (act == WAIT)
		s_data->sem = sem_wait(s_data->sem);
	else if (act == POST)
		s_data->sem = sem_post(s_data->sem);
	else if (act == CLOSE)
		s_data->sem = sem_close(s_data->sem);
	else if (act == DESTROY)
		s_data->sem = sem_unlink(s_data->path);
	else
		error_handler(INVALID_SACTION, true, data);
	if (s_data->sem == SEM_FAILED || s_data->sem == -1)
		sem_error_handler(s_data->sem, act, data);
}
