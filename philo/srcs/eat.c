/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/14 16:03:52 by hdamitzi         ###   ########.fr       */
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
	if (philo->args->nb_philo != 1)
	{
		pthread_mutex_lock(&forks[first]);
		print_state("has taken a fork", philo);
		philo->l_frk_tkn = 1;
	}
	pthread_mutex_lock(&forks[second]);
	print_state("has taken a fork", philo);
	philo->r_frk_tkn = 1;
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->args->forks;
	if (philo->r_frk_tkn &&)
	{
		pthread_mutex_unlock(&forks[philo->rfork]);
		philo->r_frk_tkn = 0;
	}
	if (philo->l_frk_tkn)
	{
		pthread_mutex_unlock(&forks[philo->lfork]);
		philo->l_frk_tkn = 0;
	}
	to_sleep(philo);
}
