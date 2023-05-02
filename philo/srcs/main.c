/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:55:24 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/02 11:58:29 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);
	while (!philo->is_dead)
	{
		take_fork('l', philo);
		if ((philo->l_fork->is_used && !philo->l_frk_taken) || (philo->r_fork->is_used && !philo->r_fork))
			to_sleep(philo);
		if (philo->l_frk_taken == 1 && !philo->r_fork->is_used)
			take_fork('r', philo);
		if (philo->l_frk_taken && philo->r_frk_taken)
		{
			printf("%d is eating\n", philo->id);
			usleep(500000);
		}
		release_fork(philo);
		think(philo);
	}
	return (0);
}

void	init_forks(t_fork **forks, t_args *args)
{
	int	i;

	i = 0;
	*forks = malloc(sizeof(t_fork) * args->nb_philo);
	if (!(*forks))
		exit(EXIT_FAILURE);
	while (i < args->nb_philo)
	{
		(*forks)[i].is_used = 0;
		pthread_mutex_init(&((*forks)[i].lock), NULL);
		i++;
	}
}

void	philo_attributes(t_philo *one_philo, t_fork **forks, int id, int nbrs)
{
	one_philo->id = id;
	one_philo->is_dead = 0;
	one_philo->r_frk_taken = 0;
	one_philo->l_frk_taken = 0;
	one_philo->r_fork = &((*forks)[id]);
	one_philo->is_dead = 0;
	if (id == (nbrs - 1))
		one_philo->l_fork = &((*forks)[0]);
	else
		one_philo->l_fork = &((*forks)[id + 1]);
}

void	init_philo(t_philo **philo, t_fork **forks, t_args *args)
{
	int	i;

	i = -1;
	*philo = malloc(sizeof(t_philo) * args->nb_philo);
	if (!(*philo))
		exit(EXIT_FAILURE);
	while (++i < args->nb_philo)
		philo_attributes(&(*philo)[i], forks, i, args->nb_philo);
}

void	parse_args(char **av, t_args *args)
{
	args->nb_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		args->max_eat = ft_atoi(av[5]);
}

int	main(int ac, char **av)
{
	t_fork	*forks;
	t_philo	*philo;
	t_args	args;

	if (ac == 5 || ac == 4)
	{
		parse_args(av, &args);
		init_forks(&forks, &args);
		init_philo(&philo, &forks, &args);
		create_threads(&philo, &args);
		philo_join(&philo, &args);
	}
	return (0);
}
