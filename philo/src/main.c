/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:31 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/19 13:11:48 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	error_handler(t_errcode err, bool is_exit, t_data *data)
{
	if (err == WRONG_INPUT)
		printf("%s[WRONG INPUT]\n\t%sUsage:%s\n\t./philo \
[number_of_philosophers] [time_to_die(ms)] [time_to_eat(ms)] \
[time_to_sleep(ms)] [number_of_meals](opt)\n\t%se.g. ./philo 5 800 200 200 [10]\
%s\n", RED, UYEL, RST, GRN, RST);
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
}

void	mutex_controller(t_mutex *mutex, t_action action, t_data *data)
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
