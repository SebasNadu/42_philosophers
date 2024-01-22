/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:58:08 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/22 18:17:40 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		mutex_controller(&philo->left_fork->mtx_fork, LOCK, philo->data);
		print_state(T_LFORK, philo);
		mutex_controller(&philo->right_fork->mtx_fork, LOCK, philo->data);
		print_state(T_RFORK, philo);
	}
	else
	{
		mutex_controller(&philo->right_fork->mtx_fork, LOCK, philo->data);
		print_state(T_RFORK, philo);
		mutex_controller(&philo->left_fork->mtx_fork, LOCK, philo->data);
		print_state(T_LFORK, philo);
	}
}

static void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		mutex_controller(&philo->left_fork->mtx_fork, UNLOCK, philo->data);
		print_state(D_LFORK, philo);
		mutex_controller(&philo->right_fork->mtx_fork, UNLOCK, philo->data);
		print_state(D_RFORK, philo);
	}
	else
	{
		mutex_controller(&philo->right_fork->mtx_fork, UNLOCK, philo->data);
		print_state(D_RFORK, philo);
		mutex_controller(&philo->left_fork->mtx_fork, UNLOCK, philo->data);
		print_state(D_LFORK, philo);
	}
}

bool	philo_eat(t_philo *philo)
{
	if (is_finished(philo->data))
		return (false);
	take_forks(philo);
	set_long(&philo->mtx_philo, &philo->last_meal_time,
		print_state(EATING, philo));
	set_size_t_plus(&philo->mtx_philo, &philo->meals_eaten);
	precise_usleep(philo->data->time_to_eat, philo->data);
	drop_forks(philo);
	if (philo->meals_eaten == philo->data->nb_meals)
		return (set_bool(&philo->mtx_philo, &philo->is_full, true), false);
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	if (is_full(philo) || is_finished(philo->data))
		return (false);
	print_state(SLEEPING, philo);
	precise_usleep(philo->data->time_to_sleep, philo->data);
	return (true);
}

bool	philo_think(t_philo	*philo, bool is_the_entry)
{
	long	time_to_think;

	if (is_full(philo) || is_finished(philo->data))
		return (false);
	if (is_the_entry == false)
		print_state(THINKING, philo);
	if (philo->data->nb_philo % 2 == 0)
		return (true);
	time_to_think = philo->data->time_to_die - 
		(philo->data->time_to_eat + philo->data->time_to_sleep);
	if (time_to_think <= 1000)
		time_to_think = 0;
	precise_usleep(time_to_think / 2, philo->data);
	return (true);
}
