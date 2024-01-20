/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:08:43 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 16:55:01 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	threads_error_handler(int status, t_action action)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_handler(THD_MEM, true, NULL);
	else if (status == EPERM)
		error_handler(THD_PERM, true, NULL);
	else if (status == EINVAL && action == CREATE)
		error_handler(THD_INV, true, NULL);
	else if (status == EINVAL && (action == JOIN || action == DETACH))
		error_handler(THD_JOIN, true, NULL);
	else if (status == ESRCH)
		error_handler(THD_ID, true, NULL);
	else if (status == EDEADLK)
		error_handler(THD_DEAD, true, NULL);
}

void	threads_controller(pthread_t *thread, void *(*function)(void *),
							void *args, t_action action)
{
	if (action == CREATE)
		threads_error_handler(pthread_create(thread, NULL, function, args),
			action);
	else if (action == JOIN)
		threads_error_handler(pthread_join(*thread, NULL), action);
	else if (action == DETACH)
		threads_error_handler(pthread_detach(*thread), action);
	else
		error_handler(INVALID_TACTION, true, NULL);
}

static void	mutex_error_handler(int status, t_action action, t_data *data)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (action == LOCK || action == UNLOCK))
		error_handler(MTX_VINV, true, data);
	else if (status == EINVAL && action == INIT)
		error_handler(MTX_AINV, true, data);
	else if (status == EDEADLK)
		error_handler(MTX_DEAD, true, data);
	else if (status == EPERM)
		error_handler(MTX_PERM, true, data);
	else if (status == ENOMEM)
		error_handler(MTX_MEM, true, data);
	else if (status == EBUSY)
		error_handler(MTX_BUSY, true, data);
}

void	mutex_controller(t_mtx *mutex, t_action action, t_data *data)
{
	if (action == INIT)
	{
		mutex_error_handler(pthread_mutex_init(&mutex->mtx, NULL),
			action, data);
		mutex->init = true;
	}
	else if (action == LOCK)
		mutex_error_handler(pthread_mutex_lock(&mutex->mtx), action, data);
	else if (action == UNLOCK)
		mutex_error_handler(pthread_mutex_unlock(&mutex->mtx), action, data);
	else if (action == DESTROY)
		mutex_error_handler(pthread_mutex_destroy(&mutex->mtx), action, data);
	else
		error_handler(INVALID_MACTION, true, data);
}
