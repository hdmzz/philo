/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/04/25 14:32:58 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_philo *philo)
{
	philo->id = philo->id;
}

void	take_fork(char fork_hand, t_philo *philo)
{
	if (fork_hand == 'l')
	{
		if (philo->l_frk_taken == 0 && philo->l_fork->is_used == 0)
		{
			pthread_mutex_lock(&(philo->l_fork->lock));
			philo->l_fork->is_used = 1;
			philo->l_frk_taken = 1;
			printf("%d has taken a left fork\n", philo->id);
			pthread_mutex_unlock(&(philo->l_fork->lock));
		}
	}
	else if (philo->r_frk_taken == 0 && philo->r_fork->is_used == 0)
	{
		pthread_mutex_lock(&(philo->r_fork->lock));
		philo->r_fork->is_used = 1;
		philo->r_frk_taken = 1;
		printf("%d has taken a right fork\n", philo->id);
		pthread_mutex_unlock(&(philo->r_fork->lock));
	}
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->l_fork->lock));
	philo->l_fork->is_used = 0;
	philo->l_frk_taken = 0;
	printf("%d released a left fork\n", philo->id);
	pthread_mutex_unlock(&(philo->l_fork->lock));
	pthread_mutex_lock(&(philo->r_fork->lock));
	philo->r_fork->is_used = 0;
	philo->r_frk_taken = 0;
	printf("%d released a right fork\n", philo->id);
	pthread_mutex_unlock(&(philo->r_fork->lock));
}
