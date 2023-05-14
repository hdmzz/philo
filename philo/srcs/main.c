/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:55:24 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/14 16:03:10 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_philo *philo)
{
	//free(philo->args->forks);
	pthread_mutex_destroy(&philo->check_meal_mutex);
	pthread_mutex_destroy(&philo->args->death_mutex);
	pthread_mutex_destroy(&philo->args->print_mutex);

}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_args	args;

	if (ac > 5 || ac < 4)
		return (0);
	parse_args(av, &args);//lock death mutex
	init_philo(&philo, &args);//death mutex locked
	create_threads(philo, &args);
	pthread_mutex_lock(&args.death_mutex);
	pthread_mutex_unlock(&args.death_mutex);
	return (0);
}
