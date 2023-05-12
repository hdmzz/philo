/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:00:09 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/12 17:53:48 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_one_philo_death(t_philo *philo)
{
	long long	lst_meal;

	pthread_mutex_lock(&philo->check_meal_mutex);
	lst_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->check_meal_mutex);
	if ((timestamp() - lst_meal) > philo->args->time_to_die)
		return (1);
	return (0);
}

void	death(t_philo *philo)
{
	int	i;
	int	dead;

	dead = 0;
	while (!dead)
	{
		i = -1;
		while (++i < philo->args->nb_philo)
		{
			if (check_one_philo_death(&philo[i]))
			{
				dead = 1;
				pthread_mutex_lock(&philo->args->death_mutex);
				philo->args->one_dead = 1;
				pthread_mutex_unlock(&philo->args->death_mutex);
				print_state("died", &philo[i]);
				break ;
			}
		}
	}
}

int	is_dead(t_args *args)
{
	int	ret;

	pthread_mutex_lock(&args->death_mutex);
	ret = args->one_dead;
	pthread_mutex_unlock(&args->death_mutex);
	return (ret);
}
