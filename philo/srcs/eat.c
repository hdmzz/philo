/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/12 20:10:50 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->args->forks;
	if (philo->args->nb_philo != 1)
	{
		pthread_mutex_lock(&forks[philo->lfork]);
		print_state("has taken a fork", philo);
		
	}
	pthread_mutex_lock(&forks[philo->rfork]);
	print_state("has taken a fork", philo);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->args->forks;
	pthread_mutex_unlock(&forks[philo->lfork]);
	pthread_mutex_unlock(&forks[philo->rfork]);
	to_sleep(philo);
}
