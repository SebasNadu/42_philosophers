/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:49:14 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/26 23:50:33 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static inline void	*print_ends(t_data *data)
{
	return (printf(MAG"%-6ld "RST"Every "YEL"Philosopher"RST" had ["CYN"%zu"RST
			"] meals, all of them "GRN"survived"RST"!🎉🎉🎉\n",
			get_time(MILLISECONDS, data) - data->start_time, data->nb_meals),
		NULL);
}

static bool	philo_status(t_philo *philo)
{
	long	elapsed;
	long	tt_die_ms;

	elapsed = get_time(MILLISECONDS, philo->data) - philo->last_meal_time;
	tt_die_ms = philo->data->time_to_die / 1e3;
	if (elapsed >= tt_die_ms)
		return (false);
	return (true);
}

void	*philo_supervisor(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	while (true)
	{
		sem_controller(&philo->data->s_supervisor, WAIT, 0, philo->data);
		if (!philo_status(philo))
		{
			print_state(DIED, philo);
			philo->is_dead = true;
			sem_controller(&philo->data->s_supervisor, POST, 0, philo->data);
			sem_controller(&philo->data->s_print, WAIT, 0, philo->data);
			exit(EXIT_SUCCESS);
		}
		sem_controller(&philo->data->s_supervisor, POST, 0, philo->data);
	}
	return (NULL);
}

void	*supervisor(void *_data)
{
	t_data	*data;
	size_t	i;

	data = (t_data *)_data;
	i = 0;
	precise_usleep(1e3, data);
	while (i < data->nb_philo)
	{
		sem_controller(&data->s_dinner_starts, POST, 0, data);
		++i;
	}
	data->start_time = get_time(MILLISECONDS, data);
	i = 0;
	while (i < data->nb_meals * data->nb_philo && !is_finished(data))
	{
		sem_controller(&data->s_meals_eaten, WAIT, 0, data);
		++i;
	}
	if (is_finished(data))
		return (NULL);
	print_ends(data);
	sem_controller(&data->s_print, WAIT, 0, data);
	kill_processes(data);
	return (NULL);
}
