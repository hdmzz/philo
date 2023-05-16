/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/16 15:01:15 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_threads(t_args *args)//main thread
{
	int			i;
	t_philo		*philo;
	pthread_t	thrd;

	i = 0;
	args->start_simulation = timestamp();
	while (i < args->nb_philo)
	{
		philo = &args->philos[i];
		pthread_create(&thrd, NULL, &routine, philo);
		pthread_mutex_lock(&args->philos[i].check_meal_mutex);
		args->philos[i].last_meal = timestamp();
		pthread_mutex_unlock(&args->philos[i].check_meal_mutex);
		pthread_detach(thrd);
		
		i++;
	}
	//death(args);
	pthread_create(&thrd, NULL, &death, (void *)args);
	pthread_join(thrd, NULL);
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
	int			dead;
	
	philo = (t_philo *)arg;
	dead = 0;
	while (!dead)
	{
		dead = philo->is_dead;
		if (dead)
			break ;
		take_fork(philo);
		if (philo->first_taken && philo->second_taken && !dead)
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
