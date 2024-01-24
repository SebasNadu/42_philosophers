/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:39:56 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/24 10:50:06 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	p_error(t_errcode err)
{
	if (err == WRONG_INPUT)
		printf("%s[WRONG INPUT]\n\t%sUsage:%s\n\t./philo \
[number_of_philosophers] [time_to_die(ms)] [time_to_eat(ms)] \
[time_to_sleep(ms)] [number_of_meals](opt)\n\t%se.g. ./philo 5 800 200 \
200 10%s\n", RED, UYEL, RST, GRN, RST);
	else if (err == NEG_NUM)
		printf(RED"[WRONG INPUT]"RST"\n\tPlease enter only positive numbers.\n");
	else if (err == NOT_NUM)
		printf("%s[WRONG INPUT]%s\n\tPlease enter only numbers.\n", RED, RST);
	else if (err == TOO_BIG)
		printf(RED"[WRONG INPUT]%s\n\tPlease enter a number between 0 and 2147483647.\
\n", RST);
	else if (err == TOO_SMALL)
		printf(RED"[WRONG INPUT]"RST"\n\tUse timestamps major than 60ms.\n");
	else if (err == ZERO_ERR)
		printf("%s[WRONG INPUT]%s\n\tPlease enter a number greater than 0 on \
the number of philos and the number of meals.\n", RED, RST);
	else if (err == INVALID_SACTION)
		printf(RED"[INVALID ACTION]"RST"\n\tPlease enter a valid action for \
sem_controller\n\t"GRN"use [OPEN] [WAIT] [POST] [CLOSE] [DESTROY]"RST);
	else if (err == INVALID_TACTION)
		printf(RED"[INVALID ACTION]"RST"\n\tPlease enter a valid action for \
threads_controller\n\t"GRN"use [CREATE] [JOIN] [DETACH]"RST);
	else if (err == MALLOC_FAIL)
		printf("%s[MALLOC FAILED]%s\n\tMalloc failed. Exiting.\n", RED, RST);
	else if (err == GETTIME_FAIL)
		printf("%s[GETTIME FAILED]%s\n\tGettime failed. Exiting.\n", RED, RST);
	else if (err == GETTIME_INV)
		printf("%s[GETTIME FAILED]%s\n\tPlease enter a valid time unit.\n\t\
%s[SECONDS][MILLISECONDS][MICROSECONDS]%s\n", RED, RST, GRN, RST);
}

static void	p_mutexerror(t_errcode err)
{
	if (err == SEM_AINV)
		printf("%s[SEMAPHORE ERROR]%s\n\tPlease enter a valid semaphore \
attribute.\n", RED, RST);
	else if (err == SEM_ACC)
		printf("%s[SEMAPHORE ERROR]%s\n\tThe semaphore exists, but the \
current process does not have access to it.\n", RED, RST);
	else if (err == SEM_TLONG)
		printf("%s[SEMAPHORE ERROR]%s\n\tThe value specified for the path is too \
long.\n", RED, RST);
	else if (err == SEM_NFILE)
		printf("%s[SEMAPHORE ERROR]%s\n\tToo many files open in the system.\n",
			RED, RST);
	else if (err == SEM_INTR)
		printf("%s[SEMAPHORE ERROR]%s\n\tThe operation was interrupted by a \
signal.\n", RED, RST);
	else if (err == SEM_OVER)
		printf("%s[SEMAPHORE ERROR]%s\n\tThe maximum allowable value for a \
semaphore would be exceeded.\n", RED, RST);
	else if (err == SEM_NON)
		printf("%s[SEMAPHORE ERROR]%s\n\tThe semaphore does not currently exist \
in the kernel.\n", RED, RST);
	else if (err == SEM_NENT)
		printf("%s[SEMAPHORE ERROR]%s\n\tO_CREAT is not set and the named \
semaphore does not exist.\n", RED, RST);
	else if (err == SEM_NSPC)
		printf("%s[SEMAPHORE ERROR]%s\n\tInsufficient space exists on the \
filesystem for the creation of the new named semaphore.\n", RED, RST);
	else if (err == SEM_DEAD)
		printf("%s[SEMAPHORE ERROR]%s\n\tA deadlock condition was detected.\n",
			RED, RST);
}

static void	p_threaderror(t_errcode err)
{
	if (err == THD_MEM)
		printf("%s[THREAD ERROR]%s\n\tInsufficient memory exists to create \
the thread.\n", RED, RST);
	else if (err == THD_PERM)
		printf("%s[THREAD ERROR]%s\n\tThe caller does not have appropriate \
permission to set the required scheduling parameters \
or scheduling policy.\n", RED, RST);
	else if (err == THD_INV)
		printf("%s[THREAD ERROR]%s\n\tThe value specified by attr is invalid.\n",
			RED, RST);
	else if (err == THD_JOIN)
		printf("%s[THREAD ERROR]%s\n\tAnother thread is already waiting to \
join with this thread.\n", RED, RST);
	else if (err == THD_ID)
		printf("%s[THREAD ERROR]%s\n\tNo thread with the ID thread could be \
found.\n", RED, RST);
	else if (err == THD_DEAD)
		printf("%s[THREAD ERROR]%s\n\tA deadlock was detected or the value \
specified by thread specifies the calling thread.\n",
			RED, RST);
}

void	error_handler(t_errcode err, bool is_exit, t_data *data)
{
	if (err >= SEM_ACC && err <= SEM_DEAD)
		p_semerror(err);
	else if (err >= THD_MEM && err <= THD_DEAD)
		p_threaderror(err);
	else
		p_error(err);
	if (is_exit)
	{
		if (data)
			free_data(data);
		exit(EXIT_FAILURE);
	}
}
