/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/11 14:19:52 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_fork(char fork_hand, t_philo *philo)
{
	pthread_mutex_t	*fork;
	int		*taken;

	fork = philo->l_fork;
	taken = &philo->l_frk_taken;
	if (fork_hand == 'r')
	{
		fork = &philo->r_fork;
		taken = &(philo->r_frk_taken);
	}
	pthread_mutex_lock(fork);
	if (!(*taken))
	{
		*taken = 1;
		print_state("has taken a fork", philo);
	}
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	if (!philo->l_frk_taken && !philo->r_frk_taken)
		to_sleep(philo);
}
