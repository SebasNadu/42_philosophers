/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:44:00 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/21 21:06:27 by sebasnadu        ###   ########.fr       */
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
# include <sys/time.h>
# include <unistd.h>

# include "colors.h"

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

typedef enum e_errcode
{
	WRONG_INPUT,
	NO_MSG,
	NEG_NUM,
	NOT_NUM,
	TOO_BIG,
	TOO_SMALL,
	ZERO_ERR,
	INVALID_MACTION,
	INVALID_TACTION,
	MALLOC_FAIL,
	GETTIME_FAIL,
	GETTIME_INV,
	MTX_VINV,
	MTX_AINV,
	MTX_DEAD,
	MTX_PERM,
	MTX_MEM,
	MTX_BUSY,
	THD_MEM,
	THD_PERM,
	THD_INV,
	THD_JOIN,
	THD_ID,
	THD_DEAD,
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

typedef enum e_time_unit
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}			t_time_unit;

typedef enum e_philo_state
{
	THINKING,
	EATING,
	SLEEPING,
	TAKING_LFORK,
	TAKING_RFORK,
	DROPPING_LFORK,
	DROPPING_RFORK,
	DIED,
}			t_philo_state;

typedef struct s_data	t_data;

typedef struct s_mtx
{
	bool			init;
	pthread_mutex_t	mtx;
}					t_mtx;

typedef struct s_fork
{
	size_t			id;
	t_mtx			mtx_fork;
}					t_fork;

typedef struct s_philo
{
	size_t			id;
	pthread_t		thread_id;
	t_mtx			mtx_philo;
	t_fork			*left_fork;
	t_fork			*right_fork;
	size_t			meals_eaten;
	long			last_meal_time;
	bool			is_full;
	t_data			*data;
}					t_philo;

struct s_data
{
	size_t			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	size_t			nb_meals;
	t_philo			*philos;
	t_fork			*forks;
	long			start_time;
	size_t			nb_philo_running;
	pthread_t		supervisor_id;
	t_mtx			mtx_supervisor;
	t_mtx			mtx_print;
	bool			dinner_starts;
	bool			dinner_ends;
};

// Parser
bool	parse_input(char **av, t_data *data);

// Init
void	init_data(t_data *data);

// Error
void	error_handler(t_errcode err, bool is_exit, t_data *data);

// Free_data
void	free_data(t_data *data);

// Utils
void	*safe_malloc(size_t bytes, t_data *data);
long	get_time(t_time_unit t_unit, t_data *data);
void	precise_usleep(long usec, t_data *data);

// Threads & Mutex
void	mutex_controller(t_mtx *mutex, t_action action, t_data *data);
void	threads_controller(pthread_t *thread, void *(*function)(void *),
			void *args, t_action action);

// Setters
void	set_size_t(t_mtx *mutex, size_t *to, size_t value);
void	set_long(t_mtx *mutex, long *to, long value);
void	set_bool(t_mtx *mutex, bool *to, bool value);
void	set_size_t_plus(t_mtx *mutex, size_t *to);

// Getters
bool	get_bool(t_mtx *mutex, bool *from);
long	get_long(t_mtx *mutex, long *from);
size_t	get_size_t(t_mtx *mutex, size_t *from);
bool	is_finished(t_data *data);

// Print
void	print_state(t_philo_state state, t_philo *philo);

// Dinner
void	*dinner(void *_philo);
void	*alone_dinner(void *_philo);

// Supervisor
void	*supervisor(void *_data);

// States
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo	*philo);

#endif
