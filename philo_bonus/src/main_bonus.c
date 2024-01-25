/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:38:27 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/25 18:07:48 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static inline void	*print_ends(t_data *data)
{
	return (printf(MAG"%-6ld "RST"Every "YEL"Philosopher"RST" had ["CYN"%zu"RST
			"] meals, all of them "GRN"survived"RST"!🎉🎉🎉\n",
			get_time(MILLISECONDS, data) - data->start_time, data->nb_meals),
		NULL);
}

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
	sem_controller(&data->s_dinner_starts, POST, 0, data);
	data->start_time = get_time(MILLISECONDS, data);
	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(-1, NULL, 0);
		++i;
	}
	if (*(size_t *)data->s_full_philos.sem == data->nb_philo)
		print_ends(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		parse_input(av, &data);
		init_data(&data);
		dinner_controller(&data);
		clean_sems(&data);
		free_sems(&data);
		free(data.philos);
	}
	else
		error_handler(WRONG_INPUT, true, NULL);
	return (0);
}
