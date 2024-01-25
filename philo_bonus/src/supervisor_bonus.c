/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:49:14 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/25 17:23:29 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static bool	philo_status(t_philo *philo)
{
	long	elapsed;
	long	tt_die_ms;

	if (is_full(philo))
		return (true);
	elapsed = get_time(MILLISECONDS, philo->data) - philo->last_meal_time;
	tt_die_ms = philo->data->time_to_die / 1e3;
	if (elapsed >= tt_die_ms)
		return (false);
	return (true);
}

void	*supervisor(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	while (!is_finished(philo->data))
	{
		sem_controller(&philo->data->s_supervisor, WAIT, 0, philo->data);
		if (philo_status(philo))
		{
			sem_controller(&philo->data->s_dinner_ends, POST, 0, philo->data);
			print_state(DIED, philo);
			sem_controller(&philo->data->s_supervisor, POST, 0, philo->data);
			return (NULL);
		}
		else if (is_full(philo))
		{
			sem_controller(&philo->data->s_supervisor, POST, 0, philo->data);
			return (NULL);
		}
		sem_controller(&philo->data->s_supervisor, POST, 0, philo->data);
	}
	return (NULL);
}
