/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:55:24 by hdamitzi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/17 15:50:01 by hdamitzi         ###   ########.fr       */
=======
/*   Updated: 2023/05/25 12:25:53 by hdamitzi         ###   ########.fr       */
>>>>>>> version-ok
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
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
	parse_args(av, &args);
	init_philo(&args);
	create_threads(&args);
	wait_and_end(&args);
	free_all(&args);
	return (0);
}
