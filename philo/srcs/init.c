/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:01:53 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/24 15:19:37 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	init_mutexes(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		pthread_mutex_init(&args->philos[i].check_meal_mutex, NULL);
	}
	pthread_mutex_init(&args->print_mutex, NULL);
	pthread_mutex_init(&args->check_death, NULL);
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
	args->forks = malloc(sizeof(pthread_mutex_t) * args->nb_philo);
	if (!args->forks)
		return ;
	init_mutexes(args);
}

int	parse_args(int ac, char **av, t_args *args)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!only_digits(av[i]))
			return (0);
	}
	args->nb_philo = ft_atoi(av[1]);
	if (args->nb_philo > 200 || args->nb_philo < 1)
		return (0);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->start_simulation = 0;
	args->one_dead = 0;
	if (av[5])
		args->max_eat = ft_atoi(av[5]);
	return (1);
}
