/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:38:27 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/24 18:56:12 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	dinner_controller(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->nb_philo == 1)
		process_controller(&data->philos[0], alone_dinner);
	else
	{
		while (i < data->nb_philo)
		{
			process_controller(&data->philos[i], dinner);
			++i;
		}
	}
	threads_controller(&data->supervisor_id, supervisor, data, CREATE);
	threads_controller(&data->supervisor_id, NULL, NULL, DETACH);
	data->start_time = get_time(MILLISECONDS, data);
	i = -1;
	while (++i < data->nb_philo)
		threads_controller(&data->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&data->mtx_supervisor, &data->dinner_ends, true);
	threads_controller(&data->supervisor_id, NULL, NULL, JOIN);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		parse_input(av, &data);
		init_data(&data);
		dinner_controller(&data);
		free_data(&data);
	}
	else
		error_handler(WRONG_INPUT, true, NULL);
	return (0);
}
