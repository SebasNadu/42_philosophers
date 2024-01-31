/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:33:45 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/31 14:42:16 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	take_forks(t_philo *philo)
{
	sem_controller(philo->left_fork, WAIT, 0, philo->data);
	print_state(T_LFORK, philo);
	sem_controller(philo->right_fork, WAIT, 0, philo->data);
	print_state(T_RFORK, philo);
}

static void	drop_forks(t_philo *philo)
{
	sem_controller(philo->left_fork, POST, 0, philo->data);
	print_state(D_LFORK, philo);
	sem_controller(philo->right_fork, POST, 0, philo->data);
	print_state(D_RFORK, philo);
}

bool	philo_eat(t_philo *philo)
{
	sem_controller(&philo->data->s_dinner_ends, WAIT, 0, philo->data);
	if (philo->is_dead == true)
		return (false);
	sem_controller(&philo->data->s_dinner_ends, POST, 0, philo->data);
	take_forks(philo);
	print_state(EATING, philo);
	sem_controller(&philo->data->s_supervisor, WAIT, 0, philo->data);
	philo->last_meal_time = get_time(MILLISECONDS, philo->data);
	philo->data->current_meals++;
	 /*sem_controller(&philo->data->s_meals_eaten, POST, 0, philo->data);*/
	sem_controller(&philo->data->s_supervisor, POST, 0, philo->data);
	precise_usleep(philo->data->time_to_eat, philo->data);
	drop_forks(philo);
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	sem_controller(&philo->data->s_dinner_ends, WAIT, 0, philo->data);
	if (philo->is_dead == true)
		return (false);
	sem_controller(&philo->data->s_dinner_ends, POST, 0, philo->data);
	print_state(SLEEPING, philo);
	precise_usleep(philo->data->time_to_sleep, philo->data);
	return (true);
}

bool	philo_think(t_philo	*philo, bool is_the_entry)
{
	long	time_to_think;

	sem_controller(&philo->data->s_dinner_ends, WAIT, 0, philo->data);
	if (philo->is_dead == true)
		return (false);
	sem_controller(&philo->data->s_dinner_ends, POST, 0, philo->data);
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
