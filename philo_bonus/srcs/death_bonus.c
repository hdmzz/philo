/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:56:15 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/31 09:47:51 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	stop_simulation(t_args *args)
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

static int	is_dead(t_philo *philo)
{
	int	i;
	int	is_full;

	i = -1;
	is_full = 1;
	if (starving_death(philo))
		return (1);
	if (philo->args->max_eat != -1 && all_full(philo->args))
		return (1);
	return (0);
}

//death sera lance par chaque process autrement dit chaque philo verifi sa propre mort
//il faudrat aussi faireen sorte quen cas de mort chaque philo puisse faire en sorte darreter tout les autres
//peut etre utiliser un semaphore que lon wait et que lon post lors de la mort de lun ce aui entraine
void	*death(void *a)
{
	t_philo	*philo;

	philo = (t_philo *)a;
	while (1)
	{
		if (is_dead(philo))
			return (NULL);
		usleep(50);
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
	sem_wait(args->stop_sem);
	stop_simulation(args);
	sem_post(args->stop_sem);
}
