/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:30:23 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 18:35:12 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->forks[i].mtx_fork.init = false;
		mutex_controller(&data->forks[i].mtx_fork, INIT, data);
		data->forks[i].id = (size_t)i;
		++i;
	}
}

static void	init_philos(t_data *data)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = data->philos + i;
		philo->id = (size_t)i + 1;
		philo->meals_eaten = 0;
		philo->mtx_philo.init = false;
		mutex_controller(&philo->mtx_philo, INIT, data);
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % data->nb_philo];
		philo->data = data;
		++i;
	}
}

void	init_data(t_data *data)
{
	data->dinner_ends = false;
	data->dinner_starts = false;
	data->philos = safe_malloc(data->nb_philo * sizeof(t_philo), data);
	data->forks = safe_malloc(data->nb_philo * sizeof(t_fork), data);
	data->mtx_supervisor.init = false;
	mutex_controller(&data->mtx_supervisor, INIT, data);
	data->mtx_print.init = false;
	mutex_controller(&data->mtx_print, INIT, data);
	init_forks(data);
	init_philos(data);
}
