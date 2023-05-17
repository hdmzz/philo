/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/17 13:18:26 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->args->forks;
	pthread_mutex_lock(&forks[philo->first]);
	print_state("has taken a fork", philo);
	philo->first_taken = 1;
	pthread_mutex_lock(&forks[philo->second]);
	print_state("has taken a fork", philo);
	philo->second_taken = 1;
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->args->forks;
	if (forks)
	{
		pthread_mutex_unlock(&forks[philo->rfork]);
		philo->first_taken = 0;
		pthread_mutex_unlock(&forks[philo->lfork]);
		philo->second_taken = 0;
	}
}
