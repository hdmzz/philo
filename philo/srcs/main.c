/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:55:24 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/26 13:24:38 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
//		pthread_mutex_destroy(&args->forks[i]);
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
