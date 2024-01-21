/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:38:35 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 21:42:03 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	get_bool(t_mtx *mutex, bool *from)
{
	bool	value;

	mutex_controller(mutex, LOCK, NULL);
	value = *from;
	mutex_controller(mutex, UNLOCK, NULL);
	return (value);
}

long	get_long(t_mtx *mutex, long *from)
{
	long	value;

	mutex_controller(mutex, LOCK, NULL);
	value = *from;
	mutex_controller(mutex, UNLOCK, NULL);
	return (value);
}

size_t	get_size_t(t_mtx *mutex, size_t *from)
{
	size_t	value;

	mutex_controller(mutex, LOCK, NULL);
	value = *from;
	mutex_controller(mutex, UNLOCK, NULL);
	return (value);
}

bool	is_finished(t_data *data)
{
	return (get_bool(&data->mtx_supervisor, &data->dinner_ends));
}
