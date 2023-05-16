/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/16 18:14:58 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;
	int				first;
	int				second;

	first = philo->lfork;
	second = philo->rfork;
	if (philo->id % 2 == 0)
	{
		first = philo->rfork;
		second = philo->lfork;
	}
	forks = philo->args->forks;
	if (philo->args->nb_philo != 1 && !philo->first_taken)
	{
		pthread_mutex_lock(&forks[first]);
		print_state("has taken a first fork", philo);
		philo->first_taken = 1;
	}
	if (!philo->second_taken)
	{
		pthread_mutex_lock(&forks[second]);//deadlock
		print_state("has taken a second fork", philo);
		philo->second_taken = 1;
	}
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
