/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:56:15 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/23 12:00:33 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	stop_simulation(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		kill(args->philos[i].pid, SIGTERM);
		i++;
	}
}

static int	starving_death(t_philo *philo)
{
	long long	cur_time;

	cur_time = timestamp();
	if ((cur_time - philo->last_meal) > philo->args->time_to_die)
	{
		print_state("died", philo);
		stop_simulation(philo->args);
		sem_post(philo->check_meal_sem);
		return (1);
	}
	return (0);
}

static int		one_is_dead(t_args *args)
{
	int	i;
	int	all_full;

	i = -1;
	all_full = 1;
	while (++i < args->nb_philo)
	{
		sem_wait(args->philos[i].check_meal_sem);
		if (starving_death(&args->philos[i]))
			return (1);
		if (args->max_eat != -1 && \
			args->philos[i].eat_count < args->max_eat)
			all_full = 0;
		sem_post(args->philos[i].check_meal_sem);
	}
	if (all_full)
	{
		stop_simulation(args);
		return (1);
	}
	return (0);
}

void	*death(void *a)
{
	t_args	*args;

	args = (t_args *)a;
	while (1)
	{
		if (one_is_dead(args))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int		check_death(t_args *args)
{
	int	ret;

	ret = 0;
	sem_wait(args->check_death_sem);
	ret = args->one_dead;
	sem_post(args->check_death_sem);
	return (ret);
}
