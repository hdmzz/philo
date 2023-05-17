/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/17 13:15:58 by hdamitzi         ###   ########.fr       */
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
		i++;
	}
	pthread_create(&args->death_thread, NULL, &death, args);
	return ;
}

void	wait_and_end(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join(args->philos[i].thrd, NULL);
		i++;
	}
	pthread_join(args->death_thread, NULL);
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

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->check_meal_mutex);
	philo->last_meal = philo->args->start_simulation;
	pthread_mutex_unlock(&philo->check_meal_mutex);
	if (philo->args->nb_philo == 1)
		return (only_one_philo(philo));
	while (check_death(philo->args) == 0 )
	{
		take_fork(philo);
		if (philo->first_taken && philo->second_taken)
		{
			print_state("is eating", philo);
			pthread_mutex_lock(&philo->check_meal_mutex);
			philo->last_meal = timestamp();
			pthread_mutex_unlock(&philo->check_meal_mutex);
			ft_sleep(philo->time_to_eat, philo->args);
			release_fork(philo);
			to_sleep(philo);
			think(philo);
		}
	}
	return (0);
}
