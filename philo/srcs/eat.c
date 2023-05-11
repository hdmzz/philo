/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/09 22:23:26 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_forks(t_fork **forks, t_args *args)
{
	int	i;

	i = 0;
	*forks = malloc(sizeof(t_fork) * args->nb_philo);
	if (!(*forks))
		exit(EXIT_FAILURE);
	while (i < args->nb_philo)
	{
		(*forks)[i].is_used = 0;
		pthread_mutex_init(&((*forks)[i].lock), NULL);
		i++;
	}
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
	if (!fork->is_used && !(*taken))
	{
		fork->is_used = 1;
		*taken = 1;
		print_state("has taken a fork", philo);
		pthread_mutex_unlock(&fork->lock);
	}
	else
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
	}
	if (philo->r_fork->is_used && philo->r_frk_taken)
	{
		pthread_mutex_lock(&(philo->r_fork->lock));
		philo->r_fork->is_used = 0;
		philo->r_frk_taken = 0;
		pthread_mutex_unlock(&(philo->r_fork->lock));
	}
	if (!philo->l_frk_taken && !philo->r_frk_taken)
	{
		to_sleep(philo);
	}
}
