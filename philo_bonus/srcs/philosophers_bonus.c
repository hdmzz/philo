/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:03:31 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/01 04:11:34 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	think(t_philo *philo)
{
	int	time_to_think;

	sem_wait(philo->check_meal_sem);
	time_to_think = (philo->args->time_to_die - \
	(timestamp() - philo->last_meal) - philo->args->time_to_eat) / 2;
	sem_post(philo->check_meal_sem);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_state("is thinking", philo);
	ft_sleep(time_to_think);
}

int	routine(t_philo *philo)
{
	pthread_create(&philo->one_death_thread, NULL, death, philo);
	pthread_detach(philo->one_death_thread);
	sem_wait(philo->check_meal_sem);
	philo->last_meal = philo->args->start_simulation;
	sem_post(philo->check_meal_sem);
	start_synchro(philo->args->start_simulation);
	if (philo->index % 2)
		think(philo);
	while (1)
	{
		take_fork(philo);
		to_sleep(philo);
		think(philo);
	}
}
