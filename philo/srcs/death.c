/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:00:09 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/14 14:48:20 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*death(void *arg)
{
	int	dead;
	t_philo	*philo;
	long long	lst_meal;

	philo = (t_philo *)arg;
	dead = 0;
	while (!dead)
	{
		pthread_mutex_lock(&philo->check_meal_mutex);
		lst_meal = philo->last_meal;
		if ((timestamp() - lst_meal) > philo->args->time_to_die)
		{
			dead = 1;
			print_state("died", philo);
			pthread_mutex_unlock(&philo->check_meal_mutex);
			pthread_mutex_lock(&philo->args->check_death);
			philo->args->one_dead = 1;
			pthread_mutex_unlock(&philo->args->check_death);
			pthread_mutex_unlock(&philo->args->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->check_meal_mutex);
	}
	return (0);
}

int	is_dead(t_args *args)
{
	int	ret;

	pthread_mutex_lock(&args->check_death);
	ret = args->one_dead;
	pthread_mutex_unlock(&args->check_death);
	return (ret);
}
