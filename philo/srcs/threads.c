/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/02 14:03:11 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_threads(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_create(&(*philo)[i].thread, NULL, &routine, &(*philo)[i]);
		i++;
	}
}

void	philo_join(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join((*philo)[i].thread, NULL);
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id %2)
		usleep(200);
	while (!philo->is_dead)
	{
		take_fork('l', philo);
		if (philo->l_frk_taken == 1 && !philo->r_fork->is_used)
			take_fork('r', philo);
		if (philo->l_frk_taken && philo->r_frk_taken)
		{
			printf("%d is eating\n", philo->id);
			usleep(philo->time_to_eat);
		}
		release_fork(philo);
		think(philo);
		to_sleep(philo);
	}
	return (0);
}
