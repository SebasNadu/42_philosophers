/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:56:34 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/24 21:19:41 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	init_philos(t_data *data)
{
	t_philo	*philo;
	sem_t	*sem;
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = data->philos + i;
		philo->id = (size_t)i + 1;
		philo->pid = 0;
		philo->meals_eaten = 0;
		philo->left_fork = data->forks;
		philo->right_fork = data->forks;
		philo->data = data;
		++i;
	}
}

static void	unlink_all(void)
{
	sem_unlink(S_FORKS);
	sem_unlink(S_NPHILO_RUNNING);
	sem_unlink(S_SUPERVISOR);
	sem_unlink(S_PRINT);
	sem_unlink(S_DINNER_STARTS);
	sem_unlink(S_DINNER_ENDS);
}

void	init_data(t_data *data)
{
	unlink_all();
	data->forks.init = false;
	data->forks.path = S_FORKS;
	data->s_nphilo_running.init = false;
	data->s_nphilo_running.path = S_NPHILO_RUNNING;
	data->s_supervisor.init = false;
	data->s_supervisor.path = S_SUPERVISOR;
	data->s_print.init = false;
	data->s_print.path = S_PRINT;
	data->s_dinner_starts.init = false;
	data->s_dinner_starts.path = S_DINNER_STARTS;
	data->s_dinner_ends.init = false;
	data->s_dinner_ends.path = S_DINNER_ENDS;
	data->s_full_philos.init = false;
	data->s_full_philos.path = S_FULL_PHILOS;
	sem_controller(&data->forks, OPEN, data->nb_philo, data);
	sem_controller(&data->s_nphilo_running, OPEN, data->nb_philo, data);
	sem_controller(&data->s_supervisor, OPEN, 1, data);
	sem_controller(&data->s_print, INIT, 1, data);
	sem_controller(&data->s_dinner_starts, 0, INIT, data);
	sem_controller(&data->s_dinner_ends, 0, INIT, data);
	sem_controller(&data->s_full_philos, 0, INIT, data);
	data->philos = safe_malloc(data->nb_philo * sizeof(t_philo), data);
	init_philos(data);
}
