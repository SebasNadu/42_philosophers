/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:53:34 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/21 01:33:48 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	all_running(t_mtx *mutex, size_t *nb_philo_running, size_t nb_philo)
{
	bool	all;

	all = false;
	mutex_controller(mutex, LOCK, NULL);
	if (*nb_philo_running == nb_philo)
		all = true;
	mutex_controller(mutex, UNLOCK, NULL);
	return (all);
}

static bool	philo_status(t_philo *philo)
{
	long	elapsed;
	long	tt_die_ms;

	if (get_bool(&philo->mtx_philo, &philo->is_full))
		return (true);
	elapsed = get_time(MILLISECONDS, philo->data) - get_long(&philo->mtx_philo,
			&philo->last_meal_time);
	tt_die_ms = philo->data->time_to_die / 1e3;
	if (elapsed >= tt_die_ms)
		return (false);
	return (true);
}

void	supervisor(t_data *data)
{
	size_t	i;

	data->start_time = get_time(MILLISECONDS, data);
	data->dinner_starts = true;
	while (!all_running(&data->mtx_supervisor, &data->nb_philo_running,
			data->nb_philo))
		;
	while (!is_finished(data))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (!philo_status(data->philos + i))
				return (set_bool(&data->mtx_supervisor, &data->dinner_ends,
						true), print_state(DIED, data->philos + i));
			i++;
		}
	}
}
