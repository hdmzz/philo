/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:00:09 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/15 13:34:16 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	death(t_philo *philo)
{
	int	dead;
	long long	lst_meal;
	int			i;

	dead = 0;
	while (!dead)
	{
		i = -1;
		while (++i < philo->args->nb_philo)
		{
			pthread_mutex_lock(&philo[i].check_meal_mutex);
			lst_meal = philo[i].last_meal;
			pthread_mutex_unlock(&philo[i].check_meal_mutex);
			if ((timestamp() - lst_meal) > philo->args->time_to_die)
			{
				print_state("died", philo);
				pthread_mutex_lock(&philo->args->check_death);
				philo->args->one_dead = 1;
				pthread_mutex_unlock(&philo->args->check_death);
				dead = 1;
			}
			// pthread_mutex_unlock(&philo[i].check_meal_mutex);
		}
	}
	printf("hello");
	return ;
}

int	is_dead(t_args *args)
{
	int	ret;

	pthread_mutex_lock(&args->check_death);
	ret = args->one_dead;
	pthread_mutex_unlock(&args->check_death);
	return (ret);
}
