/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:46:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/22 14:25:31 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	routine(t_philo *philo)
{
	sem_wait(philo->args->testsem);
	printf("sem pris philo %d\n", philo->id);
	sem_post(philo->args->testsem);
	return (1);
}

int	create_process(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		args->philos[i].pid = fork();
		if (args->philos[i].pid == 0)
			return (routine(&args->philos[i]));
		i++;
	}
	return (0);
}

int	wait_and_end(t_args *args)//le main proces doit attendre tout les process enfants
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		waitpid(args->philos[i].pid, NULL, 0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_args	args;

	parse_args(av, &args);
	init_philo(&args);
	create_process(&args);
	wait_and_end(&args);
	// free_all(&args);
	return (0);
}
