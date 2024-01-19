/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:03:20 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/19 17:40:17 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	destroy_mutex(pthread_mutex_t *mtx)
{
	int	is_locked;

	is_locked = pthread_mutex_trylock(mtx);
	if (is_locked == 0)
	{
		pthread_mutex_unlock(mtx);
		pthread_mutex_destroy(mtx);
	}
	else if (is_locked == EBUSY)
		pthread_mutex_destroy(mtx);
}

static void	free_data(t_data *data)
{
	int	i;

	i = -1;
	destroy_mutex(&data->mtx_monitor);
	while (++i < data->nb_philo)
	{
		destroy_mutex(&data->forks[i].mtx_fork);
		destroy_mutex(&data->philos[i].mtx_philo);
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
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
