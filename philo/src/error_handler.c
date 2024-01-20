/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:03:20 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/20 17:19:16 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	p_error(t_errcode err)
{
	if (err == WRONG_INPUT)
		printf("%s[WRONG INPUT]\n\t%sUsage:%s\n\t./philo \
[number_of_philosophers] [time_to_die(ms)] [time_to_eat(ms)] \
[time_to_sleep(ms)] [number_of_meals](opt)\n\t%se.g. ./philo 5 800 200 \
200 10%s\n", RED, UYEL, RST, GRN, RST);
	else if (err == NEG_NUM)
		printf("%s[WRONG INPUT]%s\n\tPlease enter only positive numbers.\n",
			RED, RST);
	else if (err == NOT_NUM)
		printf("%s[WRONG INPUT]%s\n\tPlease enter only numbers.\n", RED, RST);
	else if (err == TOO_BIG)
		printf("%s[WRONG INPUT]%s\n\tPlease enter a number between 0 and 2147483647.\
\n", RED, RST);
	else if (err == TOO_SMALL)
		printf("%s[WRONG INPUT]%s\n\tUse timestamps major than 60ms.\n",
			RED, RST);
	else if (err == ZERO_ERR)
		printf("%s[WRONG INPUT]%s\n\tPlease enter a number greater than 0 on \
the number of philos and the number of meals.\n", RED, RST);
	else if (err == INVALID_MACTION)
		printf("%s[INVALID ACTION]%s\n\tPlease enter a valid action for \
			mutex_controller\n\t%suse [LOCK] [UNLOCK] [INIT] [DESTROY]%s",
			RED, RST, GRN, RST);
	else if (err == INVALID_TACTION)
		printf("%s[INVALID ACTION]%s\n\tPlease enter a valid action for \
threads_controller\n\t%suse [CREATE] [JOIN] [DETACH]%s",
			RED, RST, GRN, RST);
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
	if (err == MTX_AINV)
		printf("%s[MUTEX ERROR]%s\n\tPlease enter a valid mutex attribute.\n",
			RED, RST);
	else if (err == MTX_VINV)
		printf("%s[MUTEX ERROR]%s\n\tPlease enter a valid mutex variable.\n",
			RED, RST);
	else if (err == MTX_DEAD)
		printf("%s[MUTEX ERROR]%s\n\tDeadlock detected.\n", RED, RST);
	else if (err == MTX_PERM)
		printf("%s[MUTEX ERROR]%s\n\tThe caller does not have the privilege \
to perform the operation.\n", RED, RST);
	else if (err == MTX_MEM)
		printf("%s[MUTEX ERROR]%s\n\tInsufficient memory exists to initialize \
the mutex.\n", RED, RST);
	else if (err == MTX_BUSY)
		printf("%s[MUTEX ERROR]%s\n\tThe mutex could not be destroyed because \
it is currently locked.\n", RED, RST);
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
	if (err >= MTX_VINV && err <= MTX_BUSY)
		p_mutexerror(err);
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
