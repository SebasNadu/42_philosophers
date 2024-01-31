/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:56:34 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/31 13:46:28 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	init_philos(t_data *data)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->pid = 0;
		philo->is_dead = false;
		philo->left_fork = &data->forks;
		philo->right_fork = &data->forks;
		philo->data = data;
		++i;
	}
}

void	init_data(t_data *data)
{
	clean_sems();
	// data->is_ended = false;
	// data->total_meals = data->nb_meals * data->nb_philo;
	// data->current_meals = 0;
	data->forks.init = false;
	data->forks.path = S_FORKS;
	data->s_supervisor.init = false;
	data->s_supervisor.path = S_SUPERVISOR;
	data->s_print.init = false;
	data->s_print.path = S_PRINT;
	data->s_dinner_starts.init = false;
	data->s_dinner_starts.path = S_DINNER_STARTS;
	data->s_dinner_ends.init = false;
	data->s_dinner_ends.path = S_DINNER_ENDS;
	data->s_is_ended.init = false;
	data->s_is_ended.path = S_IS_ENDED;
	data->s_meals_eaten.init = false;
	data->s_meals_eaten.path = S_MEALS_EATEN;
	data->philos = safe_malloc(data->nb_philo * sizeof(t_philo), data);
	sem_controller(&data->forks, OPEN, data->nb_philo, data);
	sem_controller(&data->s_supervisor, OPEN, 1, data);
	sem_controller(&data->s_print, OPEN, 1, data);
	sem_controller(&data->s_dinner_starts, OPEN, 0, data);
	sem_controller(&data->s_dinner_ends, OPEN, 1, data);
	// sem_controller(&data->s_meals_eaten, OPEN, 0, data);
	sem_controller(&data->s_is_ended, OPEN, 0, data);
	init_philos(data);
}
