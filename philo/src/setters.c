/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:51:55 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 13:55:03 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *to, bool value)
{
	mutex_controller(mutex, LOCK, NULL);
	*to = value;
	mutex_controller(mutex, UNLOCK, NULL);
}

void	set_long(ptherad_mutex_t *mutex, long *to, long value)
{
	mutex_controller(mutex, LOCK, NULL);
	*to = value;
	mutex_controller(mutex, UNLOCK, NULL);
}

void	set_size_t(pthread_mutex_t *mutex, size_t *to, size_t value)
{
	mutex_controller(mutex, LOCK, NULL);
	*to = value;
	mutex_controller(mutex, UNLOCK, NULL);
}
