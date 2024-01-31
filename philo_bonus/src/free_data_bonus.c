/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:21:24 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/31 13:33:46 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	kill_processes(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
		kill(data->philos[i++].pid, SIGTERM);
}

void	free_sems(t_data	*data)
{
	sem_controller(&data->forks, CLOSE, 0, data);
	sem_controller(&data->s_dinner_starts, CLOSE, 0, data);
	sem_controller(&data->s_dinner_ends, CLOSE, 0, data);
	sem_controller(&data->s_print, CLOSE, 0, data);
	sem_controller(&data->s_supervisor, CLOSE, 0, data);
	// sem_controller(&data->s_meals_eaten, CLOSE, 0, data);
}

void	clean_sems(void)
{
	sem_unlink(S_FORKS);
	sem_unlink(S_DINNER_STARTS);
	sem_unlink(S_DINNER_ENDS);
	sem_unlink(S_PRINT);
	sem_unlink(S_SUPERVISOR);
	/*sem_unlink(S_MEALS_EATEN);*/
}

static void	destroy_sem(t_sem *sem, t_data *data)
{
	sem_controller(sem, CLOSE, 0, data);
	sem_controller(sem, UNLINK, 0, data);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (data->forks.init)
		destroy_sem(&data->forks, data);
	if (data->s_dinner_starts.init)
		destroy_sem(&data->s_dinner_starts, data);
	if (data->s_dinner_ends.init)
		destroy_sem(&data->s_dinner_ends, data);
	if (data->s_print.init)
		destroy_sem(&data->s_print, data);
	if (data->s_supervisor.init)
		destroy_sem(&data->s_supervisor, data);
	/*if (data->s_meals_eaten.init)*/
		/*destroy_sem(&data->s_meals_eaten, data);*/
	while (++i < (int)data->nb_philo && data->philos)
	{
		if (data->philos[i].pid > 0)
			kill(data->philos[i].pid, SIGTERM);
	}
	if (data->philos)
		free(data->philos);
}
