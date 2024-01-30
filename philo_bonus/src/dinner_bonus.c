/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:21:14 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/30 21:08:45 by sebasnadu        ###   ########.fr       */
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

void	dinner(t_philo *philo)
{
	// sem_controller(&philo->data->s_nb_philo, POST, 0, philo->data);
	// while (*(int *)philo->data->s_nb_philo.sem)
	// 	;
	dinner_entry(philo);
	// while (*(int *)philo->data->s_nb_philo.sem)
	while (true)
	{
		philo_eat(philo);
		if (philo->data->nb_meals == philo->data->current_meals)
			exit(EXIT_SUCCESS);
		philo_sleep(philo);
		philo_think(philo, false);
	}
}

void	alone_dinner(t_philo *philo)
{
	print_state(T_RFORK, philo);
	precise_usleep(philo->data->time_to_die, philo->data);
	return ;
}
