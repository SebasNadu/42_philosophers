/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:52:19 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/25 16:00:39 by sebasnadu        ###   ########.fr       */
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
# include <errno.h>

# include "colors_bonus.h"
# include "structs_bonus.h"

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

// Parser_bonus
bool	parse_input(char **av, t_data *data);

// Init_bonus
void	init_data(t_data *data);

// Error_handler_bonus
void	error_handler(t_errcode err, bool is_exit, t_data *data);

// Free_data_bonus
void	free_data(t_data *data);
void	clean_sems(t_data *data);
void	free_sems(t_data	*data);

// Controllers_bonus
void	process_controller(t_philo *philo, void (*function)(t_philo *));
void	sem_controller(t_sem *s_data, t_action act, size_t size, t_data *data);
void	threads_controller(pthread_t *thread, void *(*function)(void *),
			void *args, t_action action);

// Print_bonus
long	print_state(t_philo_state state, t_philo *philo);

// Supervisor_bonus
void	*supervisor(void *_philo);

// Dinner_bonus
void	alone_dinner(t_philo *philo);
void	dinner(t_philo *philo);

// States_bonus
bool	philo_think(t_philo	*philo, bool is_the_entry);
bool	philo_sleep(t_philo *philo);
bool	philo_eat(t_philo *philo);

// Utils_bonus
bool	is_full(t_philo *philo);
bool	is_finished(t_data *data);
void	*safe_malloc(size_t bytes, t_data *data);
void	precise_usleep(long usec, t_data *data);
long	get_time(t_time_unit t_unit, t_data *data);

#endif
