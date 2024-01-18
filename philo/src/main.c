/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:31 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/18 22:33:46 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_handler(int err, bool is_exit)
{
	if (err == WRONG_INPUT)
		printf("%s[WRONG INPUT]\n\t%sUsage:%s\n\t./philo [number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep] [number_of_meals](opt)\n\
\t%se.g. ./philo 5 800 200 200 [10]%s\n", RED, UYEL, RST, GRN, RST);
	if (is_exit)
		exit(EXIT_FAILURE);
}

bool	input_parser(char **av)
{
	(void)av;
	return (true);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!input_parser(av)) //TODO: start creating struct, atoui and asignt values
			error_handler(NO_MSG, true);
	}
	else
		error_handler(WRONG_INPUT, true);
	return (0);
}
