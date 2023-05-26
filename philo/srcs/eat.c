/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/26 16:01:42 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat_sleep(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->args->forks;
	pthread_mutex_lock(&forks[philo->first]);
	print_state("has taken a fork", philo);
	pthread_mutex_lock(&forks[philo->second]);
	print_state("has taken a fork", philo);
	pthread_mutex_lock(&philo->check_meal_mutex);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->check_meal_mutex);
	print_state("is eating", philo);
	ft_sleep(philo->time_to_eat, philo->args);
	if (!check_death(philo->args))
	{
		pthread_mutex_lock(&philo->check_meal_mutex);
		philo->count_meal += 1;
		pthread_mutex_unlock(&philo->check_meal_mutex);
	}
	print_state("is sleeping", philo);
	pthread_mutex_unlock(&forks[philo->first]);
	pthread_mutex_unlock(&forks[philo->second]);
	ft_sleep(philo->time_to_sleep, philo->args);
}
