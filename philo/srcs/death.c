/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:00:09 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/16 18:08:35 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	stop_simulation(t_args *args)
{
	pthread_mutex_lock(&args->check_death);
	args->one_dead = 1;
	pthread_mutex_unlock(&args->check_death);
}

static int	starving_death(t_philo *philo)
{
	long long	cur_time;

	cur_time = timestamp();
	pthread_mutex_lock(&philo->check_meal_mutex);
	if ((cur_time - philo->last_meal) > philo->args->time_to_die)
	{
		stop_simulation(philo->args);
		print_state("died", philo);
		pthread_mutex_unlock(&philo->check_meal_mutex);
		return (1);
	}
	return (0);
}

static int		one_is_dead(t_args *args)
{
	int			i;

	i = -1;
	while (++i < args->nb_philo)
	{
		if (starving_death(&args->philos[i]))
			return (1);
	}
	return (0);
}

void	*death(void *a)
{
	t_args		*args;

	args = (t_args *)a;
	while (1)
	{
		if (one_is_dead(args))
			return (NULL);
	}
	return (NULL);
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
