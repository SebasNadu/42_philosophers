/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:45:31 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/18 23:50:48 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_handler(int err, bool is_exit)
{
	if (err == WRONG_INPUT)
		printf("%s[WRONG INPUT]\n\t%sUsage:%s\n\t./philo [number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep] [number_of_meals](opt)\n\
\t%se.g. ./philo 5 800 200 200 [10]%s\n", RED, UYEL, RST, GRN, RST);
	else if (err == NEG_NUM)
		printf("%s[WRONG INPUT]%s\n\tPlease enter only positive numbers.\n",
			RED, RST);
	else if (err == NOT_NUM)
		printf("%s[WRONG INPUT]%s\n\tPlease enter only numbers.\n", RED, RST);
	else if (err == TOO_BIG)
		printf("%s[WRONG INPUT]%s\n\tPlease enter a number between 0 and 2147483647.\
		 \n", RED, RST);
	if (is_exit)
		exit(EXIT_FAILURE);
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

const char	*check_input(const char *str)
{
	const char	*nb;
	int			len;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_handler(NEG_NUM, true);
	if (!is_digit(*str))
		error_handler(NOT_NUM, true);
	nb = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_handler(TOO_BIG, true);
	return (nb);
}

unsigned long	ft_atoul(const char *str)
{
	unsigned long	nb;

	nb = 0;
	str = check_input(str);
	while (is_digit(*str))
		nb = (nb * 10) + (*str++ - '0');
	if (nb > INT_MAX)
		error_handler(TOO_BIG, true);
	return (nb);
}

bool	input_parser(char **av, t_data *data)
{
	data->nb_philo = ft_atoul(av[1]);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!input_parser(av, &data)) //TODO: start creating struct, atoui and asignt values
			error_handler(NO_MSG, true);
	}
	else
		error_handler(WRONG_INPUT, true);
	return (0);
}
