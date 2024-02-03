/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:49:14 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/02/03 10:02:06 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static bool	philo_status(t_philo *philo)
{
	long	elapsed;
	long	tt_die_ms;

	sem_controller(&philo->data->s_supervisor, WAIT, 0, philo->data);
	elapsed = get_time(MILLISECONDS, philo->data) - philo->last_meal_time;
	tt_die_ms = philo->data->time_to_die / 1e3;
	if (elapsed >= tt_die_ms)
	{
		sem_controller(&philo->data->s_supervisor, POST, 0, philo->data);
		set_is_ended(true, philo);
		return (false);
	}
	sem_controller(&philo->data->s_supervisor, POST, 0, philo->data);
	return (true);
}

void	*philo_supervisor(void *_philo)
{
	t_philo	*philo;
	long	elap;

	philo = (t_philo *)_philo;
	elap = 0;
	while (true)
	{
		precise_usleep(100, philo->data);
		if (get_is_ended(philo))
			return (NULL);
		if (!philo_status(philo))
		{
			elap = get_time(MILLISECONDS, philo->data)
				- philo->data->start_time;
			sem_controller(&philo->data->s_print, WAIT, 0, philo->data);
			if (DEBUG_MODE)
				printf(MAG"%-6ld "RST"["CYN"%zu"RST"] 💀💀Died💀💀\n",
					elap, philo->id);
			else
				printf("%-6ld "CYN"%zu"RST" died\n", elap, philo->id);
			exit(1);
		}
	}
	return (NULL);
}
