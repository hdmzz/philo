/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:01:53 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/11 15:04:37 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_attributes(t_philo *one_philo, int id, t_args *args)
{
	one_philo->id = id + 1;
	one_philo->is_dead = 0;
	one_philo->r_frk_taken = 0;
	one_philo->l_frk_taken = 0;
	one_philo->is_dead = 0;
	one_philo->time_to_die = args->time_to_die;
	one_philo->time_to_eat = args->time_to_eat;
	one_philo->time_to_sleep = args->time_to_sleep;
	one_philo->print_mutex = args->print_mutex;
	one_philo->args = args;
	one_philo->last_meal = 0;
	pthread_mutex_init(&one_philo->r_fork, NULL);
	
}

static void	left_fork(t_philo **philo, int nb_philo, int i)//recoit chaque philo et lui assigne la fourchette gauche qui est la droite 
{
	t_philo	*cur_philo;

	cur_philo = &(*philo)[i];
	if (i == nb_philo - 1)
		cur_philo->l_fork = &(philo)[0]->r_fork;
	else
		cur_philo->l_fork = &(*philo)[i + 1].r_fork;
}

void	init_philo(t_philo **philo, t_args *args)
{
	int	i;

	i = -1;
	*philo = malloc(sizeof(t_philo) * args->nb_philo);
	if (!(*philo))
		exit(EXIT_FAILURE);
	while (++i < args->nb_philo)
		philo_attributes(&(*philo)[i], i, args);
	i = -1;
	while (++i < args->nb_philo)
		left_fork(philo, args->nb_philo, i);
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
	pthread_mutex_init(&args->print_mutex, NULL);
	pthread_mutex_init(&args->global_mutex, NULL);
	pthread_mutex_init(&args->death_mutex, NULL);
}
