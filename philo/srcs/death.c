/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:00:09 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/25 12:31:29 by hdamitzi         ###   ########.fr       */
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
		print_state("died", philo);
		stop_simulation(philo->args);
		pthread_mutex_unlock(&philo->check_meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->check_meal_mutex);
	return (0);
}

static int	all_full(t_args *args)
{
	t_philo	*philos;
	int		i;
	int		all_full;


	all_full = 1;
	i = 0;
	philos = args->philos;
	while (i < args->nb_philo)
	{
		pthread_mutex_lock(&philos[i].check_meal_mutex);
		if (philos[i].count_meal < args->max_eat)
			all_full = 0;
		pthread_mutex_unlock(&philos[i].check_meal_mutex);
		i++;
	}
	return (all_full);
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
		if (args->max_eat != -1 && all_full(args))
			stop_simulation(args);
		usleep(100);
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
