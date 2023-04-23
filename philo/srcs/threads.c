/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:33:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/04/23 18:59:00 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_threads(t_philo **philo, int nbrs_of_philo)
{
	int	i;

	i = 0;
	while (i < nbrs_of_philo)
	{
		pthread_create(&(*philo)[i].thread, NULL, &routine, &(*philo)[i]);
		i++;
	}
}


void	philo_join(t_philo **philo, int nbrs_of_philo)
{
	int	i;

	i = 0;
	while (i < nbrs_of_philo)
	{
		pthread_join((*philo)[i].thread, NULL);
		i++;
	}
}
