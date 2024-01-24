/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:49:14 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/24 22:46:30 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static bool	philo_status(t_philo *philo)
{
	long	elapsed;
	long	tt_die_ms;

	if (is_full(philo))
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
	return (printf(MAG"%-6ld "RST"Every "YEL"Philosopher"RST" had ["CYN"%zu"RST
			"] meals, all of them "GRN"survived"RST"!🎉🎉🎉\n",
			get_time(MILLISECONDS, data) - data->start_time, data->nb_meals),
		NULL);
}

static inline bool	is_dead(t_philo *philo)
{
	return (get_time() - philo->last_meal_time >= philo->data->time_to_die);
}

void	*philo_supervisor(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	while (!is_finished(philo->data))
	{
		sem_controller(&philo->data->s_supervisor, WAIT, 0, philo->data);
		if (is_dead(philo))
		{
			print_state(DIED, philo);
			sem_controller(&philo->data->s_print, WAIT, 0, philo->data);
			sem_controller(&philo->data->s_dinner_ends, POST, 0, philo->data);
			return (NULL);
		}
		sem_controller(&philo->data->s_supervisor, POST, 0, philo->data);
	}
}

// TODO: change the idea for a global supervisor, adapt is_full to a counter
void	*supervisor(void *_data)
{
	size_t	i;
	t_data	*data;
	size_t	full_philos;

	data = (t_data *)_data;
	full_philos = 0;
	sem_controller(&data->s_dinner_starts, POST, 0, data);
	while (*(int *)data->s_nphilos_running.sem)
		;
	while (!is_finished(data) && full_philos < data->nb_philo)
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
