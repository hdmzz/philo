/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:08:29 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/02 21:10:53 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	init_semaphores(t_args *args)
{
	sem_unlink("/forks_sem");
	sem_unlink("/check_death_sem");
	sem_unlink("/print_sem");
	sem_unlink("/stop_sem");
	sem_unlink(SEM_FULL);
	args->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, args->nb_philo);
	args->check_death_sem = sem_open("/check_death_sem", O_CREAT | O_RDWR, 0644, 1);
	args->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	args->stop_sem = sem_open("/stop_sem", O_CREAT, 0644, 1);
	args->full_philo_sem = sem_open(SEM_FULL, O_CREAT, 0644, args->nb_philo);
	// sem_unlink("/forks_sem");
	// sem_unlink("/check_death_sem");
	// sem_unlink("/print_sem");
	// sem_unlink("/stop_sem");
	// sem_unlink(SEM_FULL);
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
	philo->id = id + 1;
	philo->ate_enough = 0;
	philo->is_dead = 0;
	philo->time_to_die = args->time_to_die;
	philo->time_to_eat = args->time_to_eat;
	philo->time_to_sleep = args->time_to_sleep;
	philo->args = args;
	philo->last_meal = 0;
	philo->eat_count = 0;
	philo->id_in_str = ft_itoa(philo->id);
	philo->meal_sem_name = ft_strjoin("/check_meal_sem", philo->id_in_str);
	sem_unlink(philo->meal_sem_name);
	philo->check_meal_sem = sem_open(philo->meal_sem_name, O_CREAT, 0644, 1);
	sem_unlink(philo->meal_sem_name);
	free(philo->id_in_str);
	free(philo->meal_sem_name);
}

t_philo	**init_philo(t_args *args)
{
	t_philo	**philos;
	int		i;

	i = -1;
	philos = malloc(sizeof(t_philo *) * args->nb_philo);
	if (!philos)
		return (NULL);
	while (++i < args->nb_philo)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (NULL);
		philo_attributes(philos[i], i, args);
	}
	init_semaphores(args);
	return (philos);
}

static int	only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

t_args	*parse_args(int ac, char **av)
{
	int	i;
	t_args	*args;

	i = 0;
	args = malloc(sizeof(t_args) * 1);
	if (!args)
		return (NULL);
	while (++i < ac)
		if (!only_digits(av[i]))
			return (NULL);
	args->nb_philo = ft_atoi(av[1]);
	if (args->nb_philo > 200 || args->nb_philo < 1)
		return (NULL);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->start_simulation = 0;
	args->one_dead = 0;
	args->full_count = 0;
	if (av[5])
		args->max_eat = ft_atoi(av[5]);
	else
		args->max_eat = -1;
	args->philos = init_philo(args);
	return (args);
}
