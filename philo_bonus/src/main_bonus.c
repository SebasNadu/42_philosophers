/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:38:27 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/02/01 10:39:38 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	dinner_controller(t_data *data)
{
	size_t	i;
	int		status;

	i = 0;
	data->start_time = get_time(MILLISECONDS, data);
	if (data->nb_philo == 1)
		process_controller(&data->philos[0], alone_dinner);
	else
	{
		while (i < data->nb_philo)
			process_controller(&data->philos[i++], dinner);
	}
	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
			kill_processes(data);
		++i;
	}
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
