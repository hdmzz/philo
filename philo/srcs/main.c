/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:55:24 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/16 14:40:36 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_philo *philo)
{
	//free(philo->args->forks);
	pthread_mutex_destroy(&philo->check_meal_mutex);
	pthread_mutex_destroy(&philo->args->print_mutex);

}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac > 5 || ac < 4)
		return (0);
	parse_args(av, &args);
	init_philo(&args);
	create_threads(&args);
	//wait_and_end(&args);
	return (0);
}
