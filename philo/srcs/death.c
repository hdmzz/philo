/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:00:09 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/11 14:54:34 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_one_philo_death(t_philo *philo)
{
	long long	lst_meal;
	
	pthread_mutex_lock(&philo->args->global_mutex);
	lst_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->args->global_mutex);
	if ((timestamp() - lst_meal) > philo->args->time_to_die)
		return (1);
	return (0);
}

void	death(t_philo *philo)
{
	int			i;

	while(!philo->args->one_dead)
	{
		i = -1;
		while (++i < philo->args->nb_philo)
		{
			if (check_one_philo_death(&philo[i]))
			{
				pthread_mutex_lock(&philo->args->global_mutex);
				philo->args->one_dead = 1;
				pthread_mutex_unlock(&philo->args->global_mutex);
				print_state("died", &philo[i]);
				break ;
			}
		}
	}
}
