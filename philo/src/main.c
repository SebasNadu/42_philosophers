/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:31 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/25 12:07:46 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	dinner_controller(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->nb_philo == 1)
		threads_controller(&data->philos[0].thread_id, alone_dinner,
			&data->philos[0], CREATE);
	else
	{
		while (i < data->nb_philo)
		{
			threads_controller(&data->philos[i].thread_id, dinner,
				&data->philos[i], CREATE);
			++i;
		}
	}
	threads_controller(&data->supervisor_id, supervisor, data, CREATE);
	data->start_time = get_time(MILLISECONDS, data);
	set_bool(&data->mtx_supervisor, &data->dinner_starts, true);
	i = 0;
	while (i < data->nb_philo)
		threads_controller(&data->philos[i++].thread_id, NULL, NULL, JOIN);
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
