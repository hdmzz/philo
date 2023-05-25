/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:55:24 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/25 16:19:16 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_args *args)
{
	int	i;
	pthread_mutex_t	*forks;
	t_philo			*philo;

	i = -1;
	forks = args->forks;
	while (++i < args->nb_philo)
	{
		philo = &args->philos[i];
		if (philo->first_taken)
			pthread_mutex_unlock(&forks[philo->first]);
		if (philo->second_taken)
			pthread_mutex_unlock(&forks[philo->second]);
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&args->philos[i].check_meal_mutex);
	}
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->check_death);
	free(args->forks);
	free(args->philos);
	pthread_mutex_destroy(&args->print_mutex);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac - 1 < 4 || ac - 1 > 5)
		return (0);
	parse_args(ac, av, &args);
	init_philo(&args);
	create_threads(&args);
	wait_and_end(&args);
	free_all(&args);
	return (0);
}
