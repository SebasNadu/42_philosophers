/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:47:51 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/26 20:01:28 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	print_debug(t_philo_state state, t_philo *philo, long elap)
{
	if (state == T_LFORK)
		printf("%s%-6ld %s[%s%zu%s] is taking LEFT fork🍴\n", MAG, elap,
			RST, CYN, philo->id, RST);
	else if (state == T_RFORK)
		printf("%s%-6ld %s[%s%zu%s] is taking RIGHT fork🍴\n", MAG, elap,
			RST, CYN, philo->id, RST);
	else if (state == D_LFORK)
		printf(MAG"%-6ld %s[%s%zu%s] is dropping LEFT fork🍽️\n", elap,
			RST, CYN, philo->id, RST);
	else if (state == D_RFORK)
		printf(MAG"%-6ld %s[%s%zu%s] is dropping RIGHT fork🍽️\n", elap,
			RST, CYN, philo->id, RST);
	else if (state == EATING)
		printf(MAG"%-6ld "RST"["CYN"%zu"RST"] is eating🍝\n",
			elap, philo->id);
	else if (state == SLEEPING)
		printf(MAG"%-6ld "RST"["CYN"%zu"RST"] is sleeping😴\n", elap, philo->id);
	else if (state == THINKING)
		printf(MAG"%-6ld "RST"["CYN"%zu"RST"] is thinking💭\n", elap, philo->id);
	else if (state == DIED)
		printf(MAG"%-6ld "RST"["CYN"%zu"RST"] 💀💀Died💀💀\n", elap, philo->id);
}

long	print_state(t_philo_state state, t_philo *philo)
{
	long	elapsed;
	long	now;

	now = get_time(MILLISECONDS, philo->data);
	elapsed = now - philo->data->start_time;
	sem_controller(&philo->data->s_print, WAIT, 0, philo->data);
	if (DEBUG_MODE)
		print_debug(state, philo, elapsed);
	else if (state != D_RFORK && state != D_LFORK)
	{
		if ((state == T_LFORK || state == T_RFORK))
			printf("%-6ld "CYN"%zu"RST" has taken a fork\n", elapsed, philo->id);
		else if (state == EATING)
			printf("%-6ld "CYN"%zu"RST" is eating\n", elapsed, philo->id);
		else if (state == SLEEPING)
			printf("%-6ld "CYN"%zu"RST" is sleeping\n", elapsed, philo->id);
		else if (state == THINKING)
			printf("%-6ld "CYN"%zu"RST" is thinking\n", elapsed, philo->id);
		else if (state == DIED)
			printf("%-6ld "CYN"%zu"RST" died\n", elapsed, philo->id);
	}
	sem_controller(&philo->data->s_print, POST, 0, philo->data);
	return (now);
}
