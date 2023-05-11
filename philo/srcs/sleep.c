/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:16 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/11 15:33:33 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	to_sleep(t_philo *philo)
{
	print_state("is sleeping", philo);
	ft_sleep(philo->time_to_sleep);
	think(philo);
}

void	ft_sleep(long long time_to)
{
	long long	start_time;

	start_time = timestamp();
	while ((timestamp() - start_time) < time_to)
		usleep(50);
}
