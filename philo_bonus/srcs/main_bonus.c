/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:46:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/01 00:05:54 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	free_all(t_args *args)
{
	int	i;

	i = 0;
	sem_close(args->check_death_sem);
	sem_close(args->print_sem);
	sem_close(args->forks_sem);
	sem_close(args->check_death_sem);
	sem_close(args->stop_sem);
	free(args->philos);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac - 1 < 4 || ac - 1 > 5)
		return (1);
	if (!parse_args(ac, av, &args))
		exit(EXIT_FAILURE);
	init_philo(&args);
	create_process(&args);
	if (wait_and_end(&args))
		return (free_all(&args));
	free_all(&args);
	return (0);
}
