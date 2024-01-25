/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:21:14 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/25 17:09:11 by sebasnadu        ###   ########.fr       */
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
	while (!*(int *)philo->data->s_dinner_starts.sem)
		;
	philo->data->start_time = get_time(MILLISECONDS, philo->data);
	philo->last_meal_time = philo->data->start_time;
	sem_controller(&philo->data->s_nphilo_running, WAIT, 0, philo->data);
	while (*(int *)philo->data->s_nphilo_running.sem)
		;
	dinner_entry(philo);
	while (!is_finished(philo->data) && !is_full(philo))
	{
		if (!philo_eat(philo))
			return ;
		if (!philo_sleep(philo))
			return ;
		if (!philo_think(philo, false))
			return ;
	}
}

void	alone_dinner(t_philo *philo)
{
	while (!*(int *)philo->data->s_dinner_starts.sem)
		;
	philo->data->start_time = get_time(MILLISECONDS, philo->data);
	philo->last_meal_time = philo->data->start_time;
	sem_controller(&philo->data->s_nphilo_running, WAIT, 0, philo->data);
	while (*(int *)philo->data->s_nphilo_running.sem)
		;
	print_state(T_RFORK, philo);
	while (!is_finished(philo->data))
		precise_usleep(1e4, philo->data);
	return ;
}
