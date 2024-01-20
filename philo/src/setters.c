/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:51:55 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 18:37:42 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(t_mtx *mutex, bool *to, bool value)
{
	mutex_controller(mutex, LOCK, NULL);
	*to = value;
	mutex_controller(mutex, UNLOCK, NULL);
}

void	set_long(t_mtx *mutex, long *to, long value)
{
	mutex_controller(mutex, LOCK, NULL);
	*to = value;
	mutex_controller(mutex, UNLOCK, NULL);
}

void	set_size_t(t_mtx *mutex, size_t *to, size_t value)
{
	mutex_controller(mutex, LOCK, NULL);
	*to = value;
	mutex_controller(mutex, UNLOCK, NULL);
}
