/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/12 14:47:30 by hdamitzi         ###   ########.fr       */
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
	philo->last_meal = timestamp();
	if (philo->id % 2)
		usleep(philo->time_to_eat);
	while (!is_dead(philo->args))
	{
		take_fork('l', philo);
		if (philo->nbr_frk_tkn == 1)
			take_fork('r', philo);
		if (philo->nbr_frk_tkn == 2)
		{
			print_state("is eating", philo);
			philo->last_meal = timestamp();
			ft_sleep(philo->time_to_eat);
			release_fork(philo);
		}
	}
	return (0);
}
