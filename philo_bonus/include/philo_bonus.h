/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:52:19 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/24 21:23:53 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>

# include "colors_bonus.h"

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

# define S_FORKS "/forks"
# define S_NPHILO_RUNNING "/nphilo_running"
# define S_SUPERVISOR "/supervisor"
# define S_PRINT "/print"
# define S_DINNER_STARTS "/dinner_starts"
# define S_DINNER_ENDS "/dinner_ends"
# define S_FULL_PHILOS "/full_philos"

typedef enum e_errcode
{
	WRONG_INPUT,
	NO_MSG,
	NEG_NUM,
	NOT_NUM,
	TOO_BIG,
	TOO_SMALL,
	ZERO_ERR,
	INVALID_SACTION,
	INVALID_TACTION,
	MALLOC_FAIL,
	GETTIME_FAIL,
	GETTIME_INV,
	FORK_FAIL,
	SEM_ACC,
	SEM_AINV,
	SEM_TLONG,
	SEM_NFILE,
	SEM_INTR,
	SEM_OVER,
	SEM_NON,
	SEM_NENT,
	SEM_NSPC,
	SEM_DEAD,
	THD_MEM,
	THD_PERM,
	THD_INV,
	THD_JOIN,
	THD_ID,
	THD_DEAD,
}			t_errcode;

typedef enum e_action
{
	OPEN,
	WAIT,
	POST,
	CLOSE,
	UNLINK,
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
	T_LFORK,
	T_RFORK,
	D_LFORK,
	D_RFORK,
	DIED,
}			t_philo_state;

typedef struct s_data	t_data;

typedef struct s_sem
{
	const char			*path;
	bool				init;
	sem_t				*sem;
}					t_sem;

typedef struct s_philo
{
	size_t		id;
	pid_t		pid;
	t_sem		*left_fork;
	t_sem		*right_fork;
	size_t		meals_eaten;
	long		last_meal_time;
	t_data		*data;
}					t_philo;

struct s_data
{
	size_t		nb_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	size_t		nb_meals;
	t_philo		*philos;
	t_sem		forks;
	long		start_time;
	t_sem		s_nphilo_running;
	pthread_t	supervisor_id;
	t_sem		s_supervisor;
	t_sem		s_print;
	t_sem		s_dinner_starts;
	t_sem		s_dinner_ends;
	t_sem		s_full_philos;
};

#endif
