/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:31 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/21 01:38:26 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	all_ate(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten < data->nb_meals)
			return (false);
		++i;
	}
	return (true);
}

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
	supervisor(data);
	i = -1;
	while (++i < data->nb_philo)
		threads_controller(&data->philos[i].thread_id, NULL, NULL, JOIN);
	if (all_ate(data))
		print_state(DONE, &data->philos[0]);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		parse_input(av, &data);
		init_data(&data);
		dinner_controller(&data);
	}
	else
		error_handler(WRONG_INPUT, true, NULL);
	return (0);
}
