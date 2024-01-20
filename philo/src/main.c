/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:31 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 18:05:10 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	dinner(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
}

void	supervisor(t_data *data)
{
	data->start_time = get_time(MILLISECONDS);
	data->dinner_starts = true;
}

void	dinner_controller(t_data *data)
{
	int	i;

	i = -1;
	if (data->nb_philo == 1)
		threads_controller(&data->philos[0].thread_id, alone_dinner,
			&data->philos[0], CREATE);
	else
		while (++i < data->nb_philo)
			threads_controller(&data->philos[i].thread_id, dinner,
				&data->philos[i], CREATE);
	supervisor(data);
	i = -1;
	while (++i < data->nb_philo)
		threads_controller(&data->philos[i].thread_id, NULL, NULL, JOIN);
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
