/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:16 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/25 15:39:39 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	to_sleep(t_philo *philo)
{
	if (philo)
	{
		if (print_state("is sleeping", philo))
		{
			ft_sleep(philo->time_to_sleep, philo->args);
			return (1);
		}
	}
	return (0);
}

void	ft_sleep(long long time_to, t_args*args)
{
	long long	start_time;

	if (!check_death(args))
	{
		start_time = timestamp();
		while ((timestamp() - start_time) < time_to)
		{
			if (check_death(args))
				break ;
			usleep(100);
		}
	}
}
