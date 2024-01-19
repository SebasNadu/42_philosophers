/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:31 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/19 16:06:10 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	free_data(t_data *data)
{
	int	is_locked;

	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	is_locked = pthread_mutex_trylock(&data->mtx_monitor);
	if (is_locked == 0)
	{
		pthread_mutex_unlock(&data->mtx_monitor);
		pthread_mutex_destroy(&data->mtx_monitor);
	}
	else if (is_locked == EBUSY)
		pthread_mutex_destroy(&data->mtx_monitor);
}

static void	p_error(t_errcode err)
{
	if (err == WRONG_INPUT)
		printf("%s[WRONG INPUT]\n\t%sUsage:%s\n\t./philo \
[number_of_philosophers] [time_to_die(ms)] [time_to_eat(ms)] \
[time_to_sleep(ms)] [number_of_meals](opt)\n\t%se.g. ./philo 5 800 200 \
200 10%s\n", RED, UYEL, RST, GRN, RST);
	else if (err == NEG_NUM)
		printf("%s[WRONG INPUT]%s\n\tPlease enter only positive numbers.\n",
			RED, RST);
	else if (err == NOT_NUM)
		printf("%s[WRONG INPUT]%s\n\tPlease enter only numbers.\n", RED, RST);
	else if (err == TOO_BIG)
		printf("%s[WRONG INPUT]%s\n\tPlease enter a number between 0 and 2147483647.\
\n", RED, RST);
	else if (err == TOO_SMALL)
		printf("%s[WRONG INPUT]%s\n\tUse timestamps major than 60ms.\n",
			RED, RST);
	else if (err == INVALID_ACTION)
		printf("%s[INVALID ACTION]%s\n\tPlease enter a valid action for \
mutex_controller\n\t%suse [LOCK] [UNLOCK] [INIT] [DESTROY]%s",
			RED, RST, GRN, RST);
	else if (err == MALLOC_FAIL)
		printf("%s[MALLOC FAILED]%s\n\tMalloc failed. Exiting.\n", RED, RST);
}

static void	p_mutexerror(t_errcode err)
{
	if (err == MTX_MEM)
		printf("%s[MUTEX ERROR]%s\n\tThe system lacked the necessary \
resources (other than memory) to initialise another mutex.\n", RED, RST);
	else if (err == MTX_PERM)
		printf("%s[MUTEX ERROR]%s\n\tThe current thread does not own the mutex.\
\n", RED, RST);
	else if (err == MTX_INV)
		printf("%s[MUTEX ERROR]%s\n\tThe value specified by attr is invalid.\
\n", RED, RST);
	else if (err == MTX_JOIN)
		printf("%s[MUTEX ERROR]%s\n\tThe value specified by thread is not \
joinable.\n", RED, RST);
	else if (err == MTX_DEAD)
		printf("%s[MUTEX ERROR]%s\n\tA deadlock was detected or the value \
specified by mutex does not refer to an initialised mutex object.\n",
			RED, RST);
	else if (err == MTX_ID)
		printf("%s[MUTEX ERROR]%s\n\tNo thread could be found with the given \
thread ID (thread).\n", RED, RST);
}

void	error_handler(t_errcode err, bool is_exit, t_data *data)
{
	if (err >= MTX_MEM && err <= MTX_ID)
		p_mutexerror(err);
	else
		p_error(err);
	if (is_exit)
	{
		if (data)
			free_data(data);
		exit(EXIT_FAILURE);
	}
}

void	*safe_malloc(size_t bytes, t_data *data)
{
	void	*mem;

	mem = malloc(bytes);
	if (mem == NULL)
		error_handler(MALLOC_FAIL, true, data);
	return (mem);
}

void	mutex_error_handler(int status, t_action action, t_data *data)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_handler(MTX_MEM, true, data);
	else if (status == EPERM)
		error_handler(MTX_PERM, true, data);
	else if (status == EINVAL && action == CREATE)
		error_handler(MTX_INV, true, data);
	else if (status == EINVAL && (action == JOIN || action == DETACH))
		error_handler(MTX_JOIN, true, data);
	else if (status == EDEADLK)
		error_handler(MTX_DEAD, true, data);
	else if (status == ESRCH)
		error_handler(MTX_ID, true, data);
}

void	mutex_controller(pthread_mutex_t *mutex, t_action action, t_data *data)
{
	if (action == INIT)
		mutex_error_handler(pthread_mutex_init(mutex, NULL), action, data);
	else if (action == LOCK)
		mutex_error_handler(pthread_mutex_lock(mutex), action, data);
	else if (action == UNLOCK)
		mutex_error_handler(pthread_mutex_unlock(mutex), action, data);
	else if (action == DESTROY)
		mutex_error_handler(pthread_mutex_destroy(mutex), action, data);
	else
		error_handler(INVALID_ACTION, true, data);
}

void	init_data(t_data *data)
{
	int	i;

	i = -1;
	data->philos = safe_malloc(data->nb_philo * sizeof(t_philo), data);
	data->forks = safe_malloc(data->nb_philo * sizeof(t_fork), data);
	mutex_controller(&data->mtx_monitor, INIT, data);
	init_forks(data);
	init_philos(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		parse_input(av, &data);
		init_data(&data);
	}
	else
		error_handler(WRONG_INPUT, true, NULL);
	return (0);
}
