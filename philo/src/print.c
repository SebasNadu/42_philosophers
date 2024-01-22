/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:48:44 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/22 12:56:03 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_debug(t_philo_state state, t_philo *philo, long elap)
{
	if (state == T_LFORK && !is_finished(philo->data))
		printf("%s%-6ld %s[%s%zu%s] is taking LEFT fork🍴 [%s%zu%s]\n", MAG,
			elap, RST, CYN, philo->id, RST, YEL, philo->left_fork->id, RST);
	else if (state == T_RFORK
		&& !get_bool(&philo->data->mtx_supervisor, &philo->data->dinner_ends))
		printf("%s%-6ld %s[%s%zu%s] is taking RIGHT fork🍴 [%s%zu%s]\n", MAG,
			elap, RST, CYN, philo->id, RST, YEL, philo->right_fork->id, RST);
	else if (state == D_LFORK && !is_finished(philo->data))
		printf("%s%-6ld %s[%s%zu%s] is dropping LEFT fork🍽️ [%s%zu%s]\n", MAG,
			elap, RST, CYN, philo->id, RST, YEL, philo->left_fork->id, RST);
	else if (state == D_RFORK && !is_finished(philo->data))
		printf(MAG"%-6ld %s[%s%zu%s] is dropping RIGHT fork🍽️ [%s%zu%s]\n",
			elap, RST, CYN, philo->id, RST, YEL, philo->right_fork->id, RST);
	else if (state == EATING && !is_finished(philo->data))
		printf(MAG"%-6ld "RST"["CYN"%zu"RST"] is eating🍝 ["YEL"%zu"RST"]\n",
			elap, philo->id, philo->meals_eaten);
	else if (state == SLEEPING && !is_finished(philo->data))
		printf(MAG"%-6ld "RST"["CYN"%zu"RST"] is sleeping😴\n", elap, philo->id);
	else if (state == THINKING && !is_finished(philo->data))
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
	if (is_full(philo))
		return (now);
	mutex_controller(&philo->data->mtx_print, LOCK, philo->data);
	if (DEBUG_MODE)
		print_debug(state, philo, elapsed);
	else if (state != D_RFORK && state != D_LFORK)
	{
		if ((state == T_LFORK || state == T_RFORK) && !is_finished(philo->data))
			printf("%-6ld "CYN"%zu"RST" has taken a fork\n", elapsed, philo->id);
		else if (state == EATING && !is_finished(philo->data))
			printf("%-6ld "CYN"%zu"RST" is eating\n", elapsed, philo->id);
		else if (state == SLEEPING && !is_finished(philo->data))
			printf("%-6ld "CYN"%zu"RST" is sleeping\n", elapsed, philo->id);
		else if (state == THINKING && !is_finished(philo->data))
			printf("%-6ld "CYN"%zu"RST" is thinking\n", elapsed, philo->id);
		else if (state == DIED)
			printf("%-6ld "CYN"%zu"RST" died\n", elapsed, philo->id);
	}
	mutex_controller(&philo->data->mtx_print, UNLOCK, philo->data);
	return (now);
}
