/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:17:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/23 09:17:39 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	to_sleep(t_philo *philo)
{
	if (philo)
	{
		print_state("is sleeping", philo);
		ft_sleep(philo->time_to_sleep, philo->args);
	}
}
