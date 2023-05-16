/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:00:09 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/16 14:16:28 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*death(void *a)
{
	t_args		*args;
	int			i;
	int			dead;
	long long	cur_time;

	args = (t_args *)a;
	dead = 0;
	while (!dead)
	{
		i = -1;
		while (++i < args->nb_philo && !dead)
		{
			cur_time = timestamp();
			pthread_mutex_lock(&args->philos[i].check_meal_mutex);
			if ((cur_time - args->philos[i].last_meal) > args->time_to_die)
			{
				pthread_mutex_lock(&args->check_death);
				args->one_dead = 1;
				print_state("died", &args->philos[i]);
				dead = 1;
			}
			pthread_mutex_unlock(&args->philos[i].check_meal_mutex);
		}
	}
	return (0);
}

int		check_death(t_args *args)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&args->check_death);
	ret = args->one_dead;
	pthread_mutex_unlock(&args->check_death);
	return (ret);
}
