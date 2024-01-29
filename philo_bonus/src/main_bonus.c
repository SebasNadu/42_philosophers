/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:38:27 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/29 20:09:39 by sebas_nadu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	dinner_controller(t_data *data)
{
	size_t	i;
	int		status;

	i = 0;
	if (data->nb_philo == 1)
		process_controller(&data->philos[0], alone_dinner);
	else
	{
		while (i < data->nb_philo)
			process_controller(&data->philos[i++], dinner);
	}
	threads_controller(&data->supervisor_id, supervisor, data, CREATE);
	threads_controller(&data->supervisor_id, NULL, NULL, DETACH);
	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) || WIFSIGNALED(status))
			kill_processes(data);
		++i;
	}
	// set_finished(data);
	sem_controller(&data->s_is_ended, POST, 0, data);
	sem_controller(&data->s_meals_eaten, POST, 0, data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		parse_input(av, &data);
		init_data(&data);
		dinner_controller(&data);
		free_sems(&data);
		clean_sems();
		free(data.philos);
	}
	else
		error_handler(WRONG_INPUT, true, NULL);
	return (0);
}
