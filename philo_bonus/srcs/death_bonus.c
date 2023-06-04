/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:56:15 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/04 15:03:18 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	stop_simulation(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		kill(args->philos[i]->pid, SIGTERM);
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
	if ((cur_time - philo->last_meal) > philo->args->time_to_die)
	{
		sem_post(philo->check_meal_sem);
		print_state("died", philo);
		sem_post(philo->args->stop_sem);
		return (1);
	}
	sem_post(philo->check_meal_sem);
	return (0);
}

int	philo_is_full(t_philo *philo)
{
	sem_wait(philo->check_meal_sem);
	if (philo->args->max_eat > 0 && philo->eat_count > philo->args->max_eat)
	{
		philo->ate_enough = 1;
		sem_post(philo->check_meal_sem);
		sem_post(philo->args->full_philo_sem);
		sem_post(philo->args->stop_sem);
		return (1);
	}
	sem_post(philo->check_meal_sem);
	return (0);
}

static int	end_reached(t_philo *philo)
{
	long long	cur_time;
	long long	lst_meal;

	sem_wait(philo->check_meal_sem);
	if ((timestamp() - philo->last_meal) > philo->args->time_to_die)
	{
		sem_post(philo->check_meal_sem);
		sem_post(philo->args->stop_sem);
		print_state("died", philo);
		return (1);
	}
	// if (philo->eat_count >= philo->args->max_eat)
	// {
	// 	sem_post(philo->args->full_philo_sem);
	// 	sem_post(philo->check_meal_sem);
	// 	philo->ate_enough = 1;
	// 	return (1);
	// }
	sem_post(philo->check_meal_sem);
	return (0);
}

/*
*	return 1 if dead
*	join wait for the return in the parent process
*	and exit himself with one is dead
*/
void	*death(void *a)
{
	t_philo	*philo;

	philo = (t_philo *)a;
	start_synchro(philo->args->start_simulation);
	while (1)
	{
		if (starving_death(philo) || philo_is_full(philo))
			break ;
		usleep(1000);
	}
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
	sem_post(args->stop_sem);
	return (NULL);
}
