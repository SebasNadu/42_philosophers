/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:05:39 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/01/19 17:06:08 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*safe_malloc(size_t bytes, t_data *data)
{
	void	*mem;

	mem = malloc(bytes);
	if (mem == NULL)
		error_handler(MALLOC_FAIL, true, data);
	return (mem);
}
