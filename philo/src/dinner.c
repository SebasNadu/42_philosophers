/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:50:38 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/22 18:20:06 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	are_all_ready(t_data *data)
{
	while (!get_bool(&data->mtx_supervisor, &data->dinner_starts))
		;
}

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

void	*dinner(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	are_all_ready(philo->data);
	set_long(&philo->mtx_philo, &philo->last_meal_time,
		get_time(MILLISECONDS, philo->data));
	set_size_t_plus(&philo->data->mtx_supervisor,
		&philo->data->nb_philo_running);
	dinner_entry(philo);
	while (!is_finished(philo->data) && !is_full(philo))
	{
		if (!philo_eat(philo))
			return (NULL);
		if (!philo_sleep(philo))
			return (NULL);
		if (!philo_think(philo, false))
			return (NULL);
	}
	return (NULL);
}

void	*alone_dinner(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	are_all_ready(philo->data);
	set_long(&philo->mtx_philo, &philo->last_meal_time,
		get_time(MILLISECONDS, philo->data));
	set_size_t_plus(&philo->data->mtx_supervisor,
		&philo->data->nb_philo_running);
	print_state(T_RFORK, philo);
	while (!is_finished(philo->data))
		precise_usleep(1e4, philo->data);
	return (NULL);
}
