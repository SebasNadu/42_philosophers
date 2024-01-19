/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:31 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/19 18:18:27 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		mutex_controller(&data->forks[i].mtx_fork, INIT, data);
		data->forks[i].id = (size_t)i;
	}
}

void	init_philos(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		philo = data->philos + i;
		philo->id = (size_t)i + 1;
		philo->meals_eaten = 0;
		mutex_controller(&philo->mtx_philo, INIT, data);
		philo->data = data;
		if (philo->id % 2 == 0)
		{
			philo->first_fork = &data->forks[i];
			philo->second_fork = &data->forks[i + 1] % data->nb_philo;
		}
		else
		{
			philo->first_fork = &data->forks[i + 1] % data->nb_philo;
			philo->second_fork = &data->forks[i];
		}
	}
}

void	init_data(t_data *data)
{
	data->philos = safe_malloc(data->nb_philo * sizeof(t_philo), data);
	data->forks = safe_malloc(data->nb_philo * sizeof(t_fork), data);
	mutex_controller(&data->mtx_monitor, INIT, data);
	init_forks(data);
	init_philos(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		parse_input(av, &data);
		init_data(&data);
	}
	else
		error_handler(WRONG_INPUT, true, NULL);
	return (0);
}
