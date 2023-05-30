/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:24 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/30 12:57:21 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	think(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->check_meal_mutex);
	//(calcul timetodie - temps ecoule depui last meal - time-to-eat) / 2
	time_to_think = (philo->args->time_to_die- (timestamp() - philo->last_meal) - philo->args->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->check_meal_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_state("is thinking", philo);
	ft_sleep(time_to_think);
}
