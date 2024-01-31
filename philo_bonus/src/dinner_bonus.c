/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:21:14 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/31 14:38:41 by johnavar         ###   ########.fr       */
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
	// sem_controller(&philo->data->s_nb_philo, POST, 0, philo->data);
	// while (*(int *)philo->data->s_nb_philo.sem)
	// 	;
	dinner_entry(philo);
	// while (*(int *)philo->data->s_nb_philo.sem)
	while (true)
	{
		if (!philo_eat(philo))
			return (1);
		if (philo->data->nb_meals == philo->data->current_meals)
		{
			sem_controller(&philo->data->s_dinner_ends, WAIT, 0, philo->data);
			philo->is_dead = true;
			sem_controller(&philo->data->s_dinner_ends, POST, 0, philo->data);
			return (0);
		}
		if (!philo_sleep(philo))
			return (1);
		/*if (philo->is_dead == true)*/
			/*return ;*/
		if (!philo_think(philo, false))
			return (1);
	}
}

int	alone_dinner(t_philo *philo)
{
	print_state(T_RFORK, philo);
	precise_usleep(philo->data->time_to_die, philo->data);
	return (0);
}
