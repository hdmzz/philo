/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_meal_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:18:05 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/01 00:53:18 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

/*
*	this thread recover the semaphore ceded by the processes
*	when they reach the meal limit
*/
void	*are_philo_full(void *a)
{
	t_args	*args;
	int		i;

	args = (t_args *)a;
	if (args->max_eat <= 0 || args->nb_philo == 1)
		return (NULL);
	while (args->full_count < args->nb_philo)
	{
		if (check_death(args))
			return (NULL);
		sem_wait(args->full_philo_sem);
		if (!check_death(args))
			args->full_count += 1;
		else
			return (NULL);
	}
	sem_post(args->stop_sem);
}
