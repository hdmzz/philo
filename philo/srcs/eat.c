/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/28 21:14:28 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;

	if (check_death(philo->args))
		return ;
	forks = philo->args->forks;
	pthread_mutex_lock(&forks[philo->first]);
	print_state("has taken a fork", philo);
	pthread_mutex_lock(&forks[philo->second]);
	print_state("has taken a fork", philo);
	pthread_mutex_lock(&philo->check_meal_mutex);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->check_meal_mutex);
	print_state("is eating", philo);
	pthread_mutex_lock(&philo->check_meal_mutex);
	philo->count_meal += 1;
	pthread_mutex_unlock(&philo->check_meal_mutex);
	ft_sleep(philo->time_to_eat, philo->args);
	pthread_mutex_unlock(&philo->args->forks[philo->first]);
	pthread_mutex_unlock(&philo->args->forks[philo->second]);
}
