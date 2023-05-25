/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:40:30 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/23 09:37:35 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/philo_bonus.h"

void	take_fork(t_philo *philo)
{
	sem_wait(philo->args->forks_sem);
	print_state("has taken a fork", philo);
}

void	release_fork(t_philo *philo)
{
	sem_post(philo->args->forks_sem);
	sem_post(philo->args->forks_sem);
}
