/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:21:14 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/02/01 13:08:31 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	dinner_entry(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->data);
	}
	else
	{
		if (philo->id % 2 != 0)
			philo_think(philo, true);
	}
}

int	dinner(t_philo *philo)
{
	dinner_entry(philo);
	while (!get_is_ended(philo))
	{
		philo_eat(philo);
		if (philo->data->nb_meals == philo->data->current_meals
			&& !get_is_ended(philo))
		{
			set_is_ended(true, philo);
			return (0);
		}
		philo_sleep(philo);
		philo_think(philo, false);
	}
	return (1);
}

int	alone_dinner(t_philo *philo)
{
	print_state(T_RFORK, philo);
	precise_usleep(philo->data->time_to_die, philo->data);
	return (0);
}
