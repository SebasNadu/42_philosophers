/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:44:00 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/24 11:27:59 by sebasnadu        ###   ########.fr       */
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
# include <string.h>

# include "colors.h"
# include "structs.h"

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

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
bool	is_full(t_philo *philo);

// Print
long	print_state(t_philo_state state, t_philo *philo);

// Dinner
void	*dinner(void *_philo);
void	*alone_dinner(void *_philo);

// Supervisor
void	*supervisor(void *_data);

// States
bool	philo_eat(t_philo *philo);
bool	philo_sleep(t_philo *philo);
bool	philo_think(t_philo	*philo, bool is_the_entry);

#endif
