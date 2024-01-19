/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:44:00 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/19 18:08:27 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <errno.h>

# include "colors.h"

typedef enum e_errcode
{
	WRONG_INPUT,
	NO_MSG,
	NEG_NUM,
	NOT_NUM,
	TOO_BIG,
	TOO_SMALL,
	INVALID_ACTION,
	MALLOC_FAIL,
	MTX_MEM,
	MTX_PERM,
	MTX_INV,
	MTX_JOIN,
	MTX_DEAD,
	MTX_ID,
}			t_errcode;

typedef enum e_action
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_action;

typedef struct s_data	t_data;

typedef struct s_fork
{
	size_t			id;
	pthread_mutex_t	mtx_fork;
}					t_fork;

typedef struct s_philo
{
	size_t			id;
	pthread_t		thread_id;
	pthread_mutex_t	mtx_philo;
	t_fork			*first_fork;
	t_fork			*second_fork;
	size_t			meals_eaten;
	long			last_meal_time;
	t_data			*data;
}					t_philo;

struct s_data
{
	short			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	short			nb_meals;
	t_philo			*philos;
	t_fork			*forks;
	long			start_time;
	pthread_t		monitor;
	pthread_mutex_t	mtx_monitor;
};

// Parser
bool	parse_input(char **av, t_data *data);

// Error
void	error_handler(t_errcode err, bool is_exit, t_data *data);

// Utils
void	*safe_malloc(size_t bytes, t_data *data);

// Threads & Mutex
void	mutex_controller(pthread_mutex_t *mutex, t_action action, t_data *data);

#endif
