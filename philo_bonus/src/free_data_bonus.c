/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:21:24 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/24 21:23:06 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
