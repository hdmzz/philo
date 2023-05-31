/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:40:30 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/31 12:16:09 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/philo_bonus.h"

void	is_philo_full(t_philo *philo)
{
	if (philo->args->max_eat == -1)
		return ;
	if (philo->eat_count >= philo->args->max_eat)
	{
		sem_wait(philo->check_meal_sem);
		philo->ate_enough = 1;
		sem_post(philo->check_meal_sem);
	}
}

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
	is_philo_full(philo);
	sem_post(philo->args->forks_sem);
	sem_post(philo->args->forks_sem);
}
