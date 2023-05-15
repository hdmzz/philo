/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:01:53 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/15 11:47:33 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_attributes(t_philo *one_philo, int id, t_args *args)
{
	one_philo->index = id;
	one_philo->rfork = id;
	if (id == args->nb_philo - 1)
		one_philo->lfork = 0;
	else
		one_philo->lfork = id + 1;
	one_philo->id = id + 1;
	one_philo->is_dead = 0;
	one_philo->first_taken = 0;
	one_philo->second_taken = 0;
	one_philo->is_dead = 0;
	one_philo->time_to_die = args->time_to_die;
	one_philo->time_to_eat = args->time_to_eat;
	one_philo->time_to_sleep = args->time_to_sleep;
	one_philo->args = args;
	one_philo->last_meal = 0;
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
