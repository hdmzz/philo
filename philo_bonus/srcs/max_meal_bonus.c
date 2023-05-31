/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_meal_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:18:05 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/31 12:39:29 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	all_full(t_args *args)
{
	int	i;
	int	full;

	i = 0;
	full = 1;
	while (i < args->nb_philo)
	{
		sem_wait(args->philos[i].check_meal_sem);
		if (args->philos[i].ate_enough != 1)
			full = 0;
		sem_post(args->philos[i].check_meal_sem);
		i++;
	}
	return (full);
}

void	*are_philo_full(void *a)
{
	t_args	*args;
	int		i;

	printf("here");
	args = (t_args *)a;
	while (1)
	{
		if (all_full(args))
			sem_post(args->stop_sem);
	}
}
