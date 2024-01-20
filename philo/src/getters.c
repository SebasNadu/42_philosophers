/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:38:35 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 13:49:21 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	get_bool(pthread_mutex_t *mutex, bool *from)
{
	bool	value;

	mutex_controller(mutex, LOCK, NULL);
	value = *from;
	mutex_controller(mutex, UNLOCK, NULL);
	return (value);
}

long	get_long(pthread_mutex_t *mutex, long *from)
{
	long	value;

	mutex_controller(mutex, LOCK, NULL);
	value = *from;
	mutex_controller(mutex, UNLOCK, NULL);
	return (value);
}

size_t	get_size_t(pthread_mutex_t *mutex, size_t *from)
{
	size_t	value;

	mutex_controller(mutex, LOCK, NULL);
	value = *from;
	mutex_controller(mutex, UNLOCK, NULL);
	return (value);
}
