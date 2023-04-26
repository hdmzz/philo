/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/04/26 10:42:30 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_philo *philo)
{
	philo->id = philo->id;
}

void	take_fork(char fork_hand, t_philo *philo)
{
	t_fork	*fork;
	int		*taken;

	fork = philo->l_fork;
	taken = &(philo->l_frk_taken);
	if (fork_hand == 'r')
	{
		fork = philo->r_fork;
		taken = &(philo->r_frk_taken);
	}
	pthread_mutex_lock(&fork->lock);
	if (!fork->is_used )
	{
		fork->is_used = 1;
		*taken = 1;
	}
	printf("%d take a %c fork\n", philo->id, fork_hand);
	pthread_mutex_unlock(&fork->lock);
}

void	release_fork(t_philo *philo)
{
	if (philo->l_fork->is_used && philo->l_frk_taken)
	{
		pthread_mutex_lock(&(philo->l_fork->lock));
		philo->l_fork->is_used = 0;
		philo->l_frk_taken = 0;
		pthread_mutex_unlock(&(philo->l_fork->lock));
		printf("%d released a left fork\n", philo->id);
	}
	if (philo->r_fork->is_used && philo->r_frk_taken)
	{
		pthread_mutex_lock(&(philo->r_fork->lock));
		philo->r_fork->is_used = 0;
		philo->r_frk_taken = 0;
		pthread_mutex_unlock(&(philo->r_fork->lock));
		printf("%d released a right fork\n", philo->id);
	}
}
