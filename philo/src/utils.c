/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:05:39 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 17:46:50 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

	start = gettime(MICROSECONDS, data);
	while (gettime(MICROSECONDS, data) - start < usec)
	{
		elapsed = gettime(MICROSECONDS, data) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
			while (gettime(MICROSECONDS, data) - start < usec)
				return ;
	}
}

void	*safe_malloc(size_t bytes, t_data *data)
{
	void	*mem;

	mem = malloc(bytes);
	if (mem == NULL)
		error_handler(MALLOC_FAIL, true, data);
	return (mem);
}
