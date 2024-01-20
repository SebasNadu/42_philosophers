/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:40:04 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 18:36:06 by sebasnadu        ###   ########.fr       */
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

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (data->mtx_print.init)
		destroy_mutex(&data->mtx_print.mtx);
	if (data->mtx_supervisor.init)
		destroy_mutex(&data->mtx_supervisor.mtx);
	while (++i < (int)data->nb_philo)
	{
		if (data->forks[i].mtx_fork.init)
			destroy_mutex(&data->forks[i].mtx_fork.mtx);
		if (data->philos[i].mtx_philo.init)
			destroy_mutex(&data->philos[i].mtx_philo.mtx);
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}
