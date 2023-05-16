/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/16 14:21:49 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_threads(t_args *args)//main thread
{
	int			i;

	i = 0;
	args->start_simulation = timestamp();
	while (i < args->nb_philo)
	{
		if (pthread_create(&args->philos[i].thrd, NULL, &routine, (void *)&args->philos[i]) != 0)
			return ;
		pthread_mutex_lock(&args->philos[i].check_meal_mutex);
		args->philos[i].last_meal = timestamp();
		pthread_mutex_unlock(&args->philos[i].check_meal_mutex);
		i++;
	}
	//death(args);
	pthread_create(&args->death_thread, NULL, &death, (void *)args);
	pthread_detach(args->death_thread);
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
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
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
