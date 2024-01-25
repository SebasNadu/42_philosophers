/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:26:12 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/25 13:49:36 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

long	get_time(t_time_unit t_unit, t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_handler(GETTIME_FAIL, true, data);
	if (t_unit == MILLISECONDS)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (t_unit == MICROSECONDS)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (t_unit == SECONDS)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else
		error_handler(GETTIME_INV, true, data);
	return (0);
}

void	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECONDS, data);
	while (get_time(MICROSECONDS, data) - start < usec)
	{
		if (is_finished(data))
			return ;
		elapsed = get_time(MICROSECONDS, data) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
			while (get_time(MICROSECONDS, data) - start < usec)
				;
	}
}

void	*safe_malloc(size_t bytes, t_data *data)
{
	void	*mem;

	mem = malloc(bytes);
	if (mem == NULL)
		error_handler(MALLOC_FAIL, true, data);
	else
		memset(mem, 0, bytes);
	return (mem);
}

bool	is_finished(t_data *data)
{
	return (*(int *)data->s_dinner_ends.sem);
}

bool	is_full(t_philo *philo)
{
	return (philo->meals_eaten == philo->data->nb_meals);
}
