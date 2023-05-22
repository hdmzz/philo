/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:08:29 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/22 15:21:56 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	init_semaphores(t_args *args)
{
	sem_unlink("/test");
	args->testsem = sem_open("/test", O_CREAT, 0644, 3);
//Both read and write permission should be granted to each class of user that will access the semaphore
//Read permission bit for other users. Usually 04.
//Read permission bit for the group owner of the file. Usually 040
//Read permission bit for the owner of the file. On many systems this bit is 0400
//Write permission bit for the owner of the file. Usually 0200. 0200 + 0400 = 0600
//0600 +040 = 0640
//0640 + 04 = 0644
}

void	philo_attributes(t_philo *philo, int id, t_args *args)
{
	philo->index = id;
	philo->rfork = id;
	if (id == args->nb_philo - 1)
		philo->lfork = 0;
	else
		philo->lfork = id + 1;
	philo->id = id + 1;
	philo->first_taken = 0;
	philo->second_taken = 0;
	philo->is_dead = 0;
	philo->time_to_die = args->time_to_die;
	philo->time_to_eat = args->time_to_eat;
	philo->time_to_sleep = args->time_to_sleep;
	philo->args = args;
	philo->last_meal = 0;
	philo->eat_count = 0;
	philo->first = philo->lfork;
	philo->second = philo->rfork;
	if (philo->id % 2 == 0)
	{
		philo->first = philo->rfork;
		philo->second = philo->lfork;
	}
}

void	init_philo(t_args *args)
{
	int	i;

	i = -1;
	args->philos = malloc(sizeof(t_philo) * args->nb_philo);
	if (!args->philos)
		exit(EXIT_FAILURE);
	while (++i < args->nb_philo)
		philo_attributes(&args->philos[i], i, args);
	init_semaphores(args);
}

void	parse_args(char **av, t_args *args)
{
	args->nb_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->start_simulation = 0;
	args->one_dead = 0;
	if (av[5])
		args->max_eat = ft_atoi(av[5]);
}
