/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/04 22:51:33 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	all_full(t_args *args)
{
	t_philo	*philos;
	int		i;
	int		all_full;

	all_full = 1;
	i = 0;
	philos = args->philos;
	while (i < args->nb_philo)
	{
		pthread_mutex_lock(&philos[i].check_meal_mutex);
		if (philos[i].ate_enough != 1)
			all_full = 0;
		pthread_mutex_unlock(&philos[i].check_meal_mutex);
		i++;
	}
	return (all_full);
}

int	is_philo_full(t_args *args, t_philo *philo)
{
	if (args->max_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->check_meal_mutex);
	if (philo->count_meal >= args->max_eat)
	{
		philo->ate_enough = 1;
		pthread_mutex_unlock(&philo->check_meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->check_meal_mutex);
	return (0);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->args->forks;
	pthread_mutex_lock(&forks[philo->first]);
	print_state("has taken a fork", philo);
	pthread_mutex_lock(&forks[philo->second]);
	print_state("has taken a fork", philo);
	print_state("is eating", philo);
	pthread_mutex_lock(&philo->check_meal_mutex);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->check_meal_mutex);
	ft_sleep(philo->time_to_eat);
	philo->count_meal += 1;
	is_philo_full(philo->args, philo);
	pthread_mutex_unlock(&philo->args->forks[philo->first]);
	pthread_mutex_unlock(&philo->args->forks[philo->second]);
}
