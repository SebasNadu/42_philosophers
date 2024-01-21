/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:58:08 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 22:53:55 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	pick_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		mutex_controller(&philo->left_fork->mtx_fork, LOCK, philo->data);
		print_state(TAKING_LFORK, philo);
		mutex_controller(&philo->right_fork->mtx_fork, LOCK, philo->data);
		print_state(TAKING_RFORK, philo);
	}
	else
	{
		mutex_controller(&philo->right_fork->mtx_fork, LOCK, philo->data);
		print_state(TAKING_RFORK, philo);
		mutex_controller(&philo->left_fork->mtx_fork, LOCK, philo->data);
		print_state(TAKING_LFORK, philo);
	}
}

static void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		mutex_controller(&philo->left_fork->mtx_fork, UNLOCK, philo->data);
		print_state(DROPPING_LFORK, philo);
		mutex_controller(&philo->right_fork->mtx_fork, UNLOCK, philo->data);
		print_state(DROPPING_RFORK, philo);
	}
	else
	{
		mutex_controller(&philo->right_fork->mtx_fork, UNLOCK, philo->data);
		print_state(DROPPING_RFORK, philo);
		mutex_controller(&philo->left_fork->mtx_fork, UNLOCK, philo->data);
		print_state(DROPPING_LFORK, philo);
	}
}

void	philo_eat(t_philo *philo)
{
	pick_forks(philo);
	mutex_controller(&philo->data->mtx_supervisor, LOCK, philo->data);
	set_long(&philo->mtx_philo, &philo->last_meal_time,
		get_time(MILLISECONDS, philo->data));
	philo->meals_eaten++;
	mutex_controller(&philo->data->mtx_supervisor, UNLOCK, philo->data);
	print_state(EATING, philo);
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->meals_eaten == philo->data->nb_meals)
		set_bool(&philo->mtx_philo, &philo->is_full, true);
	drop_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_state(SLEEPING, philo);
	precise_usleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo	*philo)
{
	print_state(THINKING, philo);
}
