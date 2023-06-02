/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:56:15 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/01 03:03:11 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	stop_simulation(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		kill(args->philos[i].pid, SIGTERM);
		i++;
	}
	return (1);
}

static int	starving_death(t_philo *philo)
{
	long long	cur_time;
	long long	lst_meal;

	cur_time = timestamp();
	sem_wait(philo->check_meal_sem);
	lst_meal = philo->last_meal;
	if ((cur_time - philo->last_meal) > philo->args->time_to_die)
	{
		print_state("died", philo);
		sem_post(philo->check_meal_sem);
		sem_post(philo->args->stop_sem);
		return (1);
	}
	sem_post(philo->check_meal_sem);
	return (0);
}

int	philo_is_full(t_philo *philo)
{
	int	eat_count;

	sem_wait(philo->check_meal_sem);
	eat_count = philo->eat_count;
	sem_post(philo->check_meal_sem);
	if (eat_count < philo->args->max_eat)
		return (0);
	sem_post(philo->args->full_philo_sem);
	philo->ate_enough = 1;
	return (1);
}

static int	end_reached(t_philo *philo)
{
	if (starving_death(philo) || philo_is_full(philo))
		return (1);
	return (0);
}

void	*death(void *a)
{
	t_philo	*philo;

	philo = (t_philo *)a;
	start_synchro(philo->args->start_simulation);
	sem_wait(philo->args->full_philo_sem);
	while (!end_reached(philo))
	{
		usleep(1000);
	}
	return (NULL);
}

int	check_death(t_args *args)
{
	int	ret;

	ret = 0;
	sem_wait(args->check_death_sem);
	ret = args->one_dead;
	sem_post(args->check_death_sem);
	return (ret);
}

void	*global_death(void *a)
{
	t_args	*args;

	args = (t_args *)a;
	start_synchro(args->start_simulation);
	sem_wait(args->stop_sem);
	stop_simulation(args);
	return (0);
}
