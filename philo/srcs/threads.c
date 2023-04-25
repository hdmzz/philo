/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/04/25 12:44:23 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_threads(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_create(&(*philo)[i].thread, NULL, &routine, &(*philo)[i]);
		i++;
	}
}

void	philo_join(t_philo **philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join((*philo)[i].thread, NULL);
		i++;
	}
}
