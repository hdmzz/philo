/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/12 19:42:48 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_threads(t_philo *philo, t_args *args)
{
	int			i;
	pthread_t	*thrd;

	i = 0;
	args->start_simulation = timestamp();
	thrd = malloc(sizeof(pthread_t) * args->nb_philo);
	if (!thrd)
		return ;
	while (i < args->nb_philo)
	{
		if (pthread_create(&thrd[i], NULL, &routine, (void *)&philo[i]))
			return ;
		pthread_mutex_lock(&philo[i].check_meal_mutex);
		philo[i].last_meal = timestamp();
		pthread_mutex_unlock(&philo[i].check_meal_mutex);
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
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(philo->time_to_eat);
	while (!is_dead(philo->args))
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
