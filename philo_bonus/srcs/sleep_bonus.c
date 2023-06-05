/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:17:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/30 16:18:40 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	to_sleep(t_philo *philo)
{
	print_state("is sleeping", philo);
	ft_sleep(philo->time_to_sleep);
}

void	ft_sleep(long long time_to)
{
	long long	start_time;

	start_time = timestamp();
	while ((timestamp() - start_time) < time_to)
		usleep(100);
}
