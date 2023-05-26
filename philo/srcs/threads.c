/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/26 13:27:47 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_threads(t_args *args)//main thread
{
	int			i;
	t_philo		*philo;

	i = 0;
	args->start_simulation = timestamp();
	while (i < args->nb_philo)
	{
		philo = &args->philos[i];
		pthread_create(&philo->thrd, NULL, &routine, philo);
		pthread_mutex_lock(&philo->check_meal_mutex);
		philo->last_meal = philo->args->start_simulation;
		pthread_mutex_unlock(&philo->check_meal_mutex);
		i++;
	}
	death(args);
	return ;
}

void	wait_and_end(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pthread_join(args->philos[i].thrd, NULL))
			return ;
		i++;
	}
}

static void	*only_one_philo(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->args->forks;
	pthread_mutex_lock(&forks[philo->first]);
	print_state("has taken a fork", philo);
	ft_sleep(philo->time_to_die, philo->args);
	pthread_mutex_unlock(&forks[philo->first]);
	return (NULL);
}

void	unlock_destroy_mtx(t_philo *philo)
{
	if (philo->first_taken)
	{
		pthread_mutex_unlock(&philo->args->forks[philo->first]);
		pthread_mutex_destroy(&philo->args->forks[philo->first]);
	}
	else if (philo->second_taken)
	{
		pthread_mutex_unlock(&philo->args->forks[philo->second]);
		pthread_mutex_destroy(&philo->args->forks[philo->second]);
	}
	else
		return ;
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->args->nb_philo == 1)
		return (only_one_philo(philo));
	while (1)
	{
		if (!take_fork(philo))
			return (0);
		if (philo->first_taken && philo->second_taken)
		{
			if (!print_state("is eating", philo))
			{
				release_fork(philo);
				break ;
			}
			pthread_mutex_lock(&philo->check_meal_mutex);
			philo->last_meal = timestamp();
			philo->count_meal += 1;
			pthread_mutex_unlock(&philo->check_meal_mutex);
			ft_sleep(philo->time_to_eat, philo->args);
			release_fork(philo);
			if (!to_sleep(philo))
				break ;
			if (!think(philo))
				break ;
		}
	}
	unlock_destroy_mtx(philo);
	return (NULL);
}
