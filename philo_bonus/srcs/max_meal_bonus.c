/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_meal_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:18:05 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/31 19:32:49 by hdamitzi         ###   ########.fr       */
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
		if (args->philos[i].ate_enough == 0)
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

	args = (t_args *)a;
	while (1)
	{
		if (all_full(args))
			printf ("\nOK\n") ;
		usleep(1000);
	}
	sem_post(args->stop_sem);
}
