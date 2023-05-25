/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/25 16:07:02 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;

	if (check_death(philo->args))
		return (0);
	forks = philo->args->forks;
	pthread_mutex_lock(&forks[philo->first]);
	print_state("has taken a fork", philo);
	philo->first_taken = 1;
	if (check_death(philo->args))
		return (0);
	pthread_mutex_lock(&forks[philo->second]);
	print_state("has taken a fork", philo);
	philo->second_taken = 1;
	return (1);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->args->forks;
	pthread_mutex_unlock(&forks[philo->rfork]);
	philo->first_taken = 0;
	pthread_mutex_unlock(&forks[philo->lfork]);
	philo->second_taken = 0;
}
