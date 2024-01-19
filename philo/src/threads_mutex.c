/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:08:43 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/19 17:09:23 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	mutex_error_handler(int status, t_action action, t_data *data)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_handler(MTX_MEM, true, data);
	else if (status == EPERM)
		error_handler(MTX_PERM, true, data);
	else if (status == EINVAL && action == CREATE)
		error_handler(MTX_INV, true, data);
	else if (status == EINVAL && (action == JOIN || action == DETACH))
		error_handler(MTX_JOIN, true, data);
	else if (status == EDEADLK)
		error_handler(MTX_DEAD, true, data);
	else if (status == ESRCH)
		error_handler(MTX_ID, true, data);
}

void	mutex_controller(pthread_mutex_t *mutex, t_action action, t_data *data)
{
	if (action == INIT)
		mutex_error_handler(pthread_mutex_init(mutex, NULL), action, data);
	else if (action == LOCK)
		mutex_error_handler(pthread_mutex_lock(mutex), action, data);
	else if (action == UNLOCK)
		mutex_error_handler(pthread_mutex_unlock(mutex), action, data);
	else if (action == DESTROY)
		mutex_error_handler(pthread_mutex_destroy(mutex), action, data);
	else
		error_handler(INVALID_ACTION, true, data);
}
