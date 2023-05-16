/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:16 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/16 14:17:55 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	to_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->check_death);
	if (philo->args->one_dead)
	{
		pthread_mutex_unlock(&philo->args->check_death);
		return ;
	}
	pthread_mutex_unlock(&philo->args->check_death);
	print_state("is sleeping", philo);
	ft_sleep(philo->time_to_sleep, philo->args);
}

void	ft_sleep(long long time_to, t_args*args)
{
	long long	start_time;

	if (!check_death(args))
	{
		start_time = timestamp();
		while ((timestamp() - start_time) < time_to)
			usleep(50);
	}
}
