/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/12 13:30:37 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_fork(char fork_hand, t_philo *philo)
{
	pthread_mutex_t	*fork;
	int		*taken;

	fork = philo->l_fork;
	taken = &philo->nbr_frk_tkn;
	if (fork_hand == 'r')
		fork = &philo->r_fork;
	if (!(*taken == philo->args->nb_philo && philo->args->nb_philo == 1))
	{
		pthread_mutex_lock(fork);
		*taken += 1;
		print_state("has taken a fork", philo);
	}
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	to_sleep(philo);
}
