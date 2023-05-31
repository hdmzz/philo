/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:40:30 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/01 01:03:29 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/philo_bonus.h"

void	take_fork(t_philo *philo)
{
	sem_wait(philo->args->forks_sem);
	print_state("has taken a fork", philo);
	sem_wait(philo->args->forks_sem);
	print_state("has taken a fork", philo);
	print_state("is eating", philo);
	sem_wait(philo->check_meal_sem);
	philo->last_meal = timestamp();
	sem_post(philo->check_meal_sem);
	ft_sleep(philo->time_to_eat);
	philo->eat_count += 1;
	sem_post(philo->args->forks_sem);
	sem_post(philo->args->forks_sem);
}
