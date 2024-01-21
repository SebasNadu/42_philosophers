/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:50:38 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/21 00:39:15 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*alone_dinner(void *_philo)
{
	(void)_philo;
	return (NULL);
}

static void	philo_entry(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(2e4, philo->data);
	}
	else
	{
		if (philo->id % 2 != 0)
			precise_usleep(2e4, philo->data);
	}
}

void	*dinner(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	while (!get_bool(&philo->data->mtx_supervisor,
			&philo->data->dinner_starts))
		;
	set_size_t_plus(&philo->mtx_philo, &philo->data->nb_philo_running);
	set_long(&philo->mtx_philo, &philo->last_meal_time,
		get_time(MILLISECONDS, philo->data));
	philo_entry(philo);
	while (!get_bool(&philo->data->mtx_supervisor, &philo->data->dinner_ends)
		&& !get_bool(&philo->mtx_philo, &philo->is_full))
	{
		if (get_bool(&philo->mtx_philo, &philo->is_full))
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
