/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:21:24 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/25 13:24:21 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_sems(t_data	*data)
{
	sem_controller(&data->forks, CLOSE, 0, data);
	sem_controller(&data->s_nphilo_running, CLOSE, 0, data);
	sem_controller(&data->s_dinner_starts, CLOSE, 0, data);
	sem_controller(&data->s_dinner_ends, CLOSE, 0, data);
	sem_controller(&data->s_print, CLOSE, 0, data);
	sem_controller(&data->s_supervisor, CLOSE, 0, data);
	sem_controller(&data->s_full_philos, CLOSE, 0, data);
}

void	clean_sems(t_data *data)
{
	sem_controller(&data->forks, UNLINK, 0, data);
	sem_controller(&data->s_nphilo_running, UNLINK, 0, data);
	sem_controller(&data->s_dinner_starts, UNLINK, 0, data);
	sem_controller(&data->s_dinner_ends, UNLINK, 0, data);
	sem_controller(&data->s_print, UNLINK, 0, data);
	sem_controller(&data->s_supervisor, UNLINK, 0, data);
	sem_controller(&data->s_full_philos, UNLINK, 0, data);
}

static void	destroy_sem(t_sem *sem, t_data *data)
{
	sem_controller(sem, UNLINK, 0, data);
	sem_controller(sem, CLOSE, 0, data);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (data->forks.init)
		destroy_sem(&data->forks, data);
	if (data->s_nphilo_running.init)
		destroy_sem(&data->s_nphilo_running, data);
	if (data->s_dinner_starts.init)
		destroy_sem(&data->s_dinner_starts, data);
	if (data->s_dinner_ends.init)
		destroy_sem(&data->s_dinner_ends, data);
	if (data->s_print.init)
		destroy_sem(&data->s_print, data);
	if (data->s_supervisor.init)
		destroy_sem(&data->s_supervisor, data);
	if (data->s_full_philos.init)
		destroy_sem(&data->s_full_philos, data);
	while (++i < (int)data->nb_philo)
	{
		if (data->philos[i].pid > 0)
			kill(data->philos[i].pid, SIGTERM);
	}
	if (data->philos)
		free(data->philos);
}
