/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:53:34 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/21 21:47:54 by sebasnadu        ###   ########.fr       */
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

static inline void	*print_ends(t_data *data)
{
	return (printf("\tEvery "YEL"Philosopher"RST" had ["CYN"%zu"RST"] meals, all \
of them "GRN"survived"RST"!🎉🎉🎉\n", data->nb_meals), NULL);
}

void	*supervisor(void *_data)
{
	size_t	i;
	t_data	*data;

	data = (t_data *)_data;
	while (!all_running(&data->mtx_supervisor, &data->nb_philo_running,
			data->nb_philo))
		;
	while (!is_finished(data))
	{
		i = 0;
		while (i < data->nb_philo && !is_finished(data))
		{
			if (!philo_status(data->philos + i))
			{
				set_bool(&data->mtx_supervisor, &data->dinner_ends, true);
				print_state(DIED, data->philos + i);
				return (NULL);
			}
			i++;
		}
	}
	return (print_ends(data));
}
