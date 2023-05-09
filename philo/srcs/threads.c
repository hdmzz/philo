/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/09 20:46:10 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_threads(t_philo *philo, t_args *args)
{
	int	i;
	pthread_t	*thrd;

	i = 0;
	thrd = malloc(sizeof(pthread_t) * args->nb_philo);
	while (i < args->nb_philo)
	{
		if (pthread_create(&thrd[i], NULL, &routine, (void *)&philo[i]))
			return ;
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join(thrd[i], NULL);
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
	if (philo->id % 2 != 0)
		usleep(philo->time_to_eat);
	while (!philo->is_dead)
	{
		take_fork('l', philo);
		if (philo->l_frk_taken == 1 && !philo->r_fork->is_used)
			take_fork('r', philo);
		if (philo->l_frk_taken && philo->r_frk_taken)
		{
			print_state("is eating", philo);
			usleep(philo->time_to_eat);
			release_fork(philo);
		}
	}
	return (0);
}
