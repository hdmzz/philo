/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/14 15:43:07 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_threads(t_philo *philo, t_args *args)//main thread
{
	int			i;
	pthread_t	*thrd;

	i = 0;
	thrd = malloc(sizeof(pthread_t) * args->nb_philo);
	args->start_simulation = timestamp();
	while (i < args->nb_philo)
	{
		
		if (pthread_create(&thrd[i], NULL, &routine, (void *)&philo[i]) != 0)
			return ;
		pthread_mutex_lock(&philo[i].check_meal_mutex);
		philo[i].last_meal = timestamp();
		pthread_mutex_unlock(&philo[i].check_meal_mutex);
		//pthread_detach(thrd);
		i++;
	}
	death(philo);
	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join(thrd[i], NULL);
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo		*philo;
	// pthread_t	thrd;

	philo = (t_philo *)arg;
	// pthread_create(&thrd, NULL, &death, philo);
	// pthread_detach(thrd);
	while (1)
	{
		take_fork(philo);
		print_state("is eating", philo);
		pthread_mutex_lock(&philo->check_meal_mutex);
		philo->last_meal = timestamp();
		pthread_mutex_unlock(&philo->check_meal_mutex);
		ft_sleep(philo->time_to_eat);
		release_fork(philo);
	}
	return (0);
}
