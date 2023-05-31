/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:46:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/30 16:19:49 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

// static int	only_one_philo(t_philo *philo)
// {
// 	pthread_create(&philo->one_death_thread, NULL, death, philo);
// 	pthread_detach(philo->one_death_thread);
// 	sem_wait(philo->args->forks_sem);
// 	print_state("has taken a fork", philo);
// 	ft_sleep(philo->time_to_die, philo->args);
// 	return (1);
// }

void	think(t_philo *philo)
{
	print_state("is thinking", philo);
}

int	routine(t_philo *philo)
{
	sem_wait(philo->check_meal_sem);
	philo->last_meal = timestamp();
	sem_post(philo->check_meal_sem);
	pthread_create(&philo->one_death_thread, NULL, death, philo);
	pthread_detach(philo->one_death_thread);
	while (1)
	{
		take_fork(philo);
		release_fork(philo);
		to_sleep(philo);
		think(philo);
	}
	return (1);
}

int	create_process(t_args *args)
{
	int	i;

	i = 0;
	args->start_simulation = timestamp();
	sem_wait(args->stop_sem);
	while (i < args->nb_philo)
	{
		args->philos[i].pid = fork();
		if (args->philos[i].pid == 0)
			return (routine(&args->philos[i]));
		i++;
	}
	pthread_create(&args->death_thread, NULL, &global_death, args);
	pthread_join(args->death_thread, NULL);
	return (0);
}

int	wait_and_end(t_args *args)
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

	if (ac - 1 < 4 || ac - 1 > 5)
		return (1);
	if (!parse_args(ac, av, &args))
		exit(EXIT_FAILURE);
	init_philo(&args);
	create_process(&args);
	wait_and_end(&args);
	return (0);
}
