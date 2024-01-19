/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:53:27 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/19 12:27:46 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*check_input(const char *str)
{
	const char	*nb;
	int			len;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_handler(NEG_NUM, true, NULL);
	if (!is_digit(*str))
		error_handler(NOT_NUM, true, NULL);
	nb = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_handler(TOO_BIG, true, NULL);
	return (nb);
}

static long	ft_atol(const char *str)
{
	long	nb;

	nb = 0;
	str = check_input(str);
	while (is_digit(*str))
		nb = (nb * 10) + (*str++ - '0');
	if (nb > INT_MAX)
		error_handler(TOO_BIG, true, NULL);
	return (nb);
}

bool	parse_input(char **av, t_data *data)
{
	data->nb_philo = (short)ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]) * 1e3;
	data->time_to_eat = ft_atol(av[3]) * 1e3;
	data->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4
		|| data->time_to_sleep < 6e4)
		error_handler(TOO_SMALL, true, NULL);
	if (av[5])
		data->nb_meals = (short)ft_atol(av[5]);
	else
		data->nb_meals = -1;
	return (true);
}
