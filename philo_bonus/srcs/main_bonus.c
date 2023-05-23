/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:46:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/23 11:53:37 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	only_one_philo(t_philo *philo)
{
	sem_wait(philo->args->forks_sem);
	print_state("has taken a fork", philo);
	ft_sleep(philo->time_to_die, philo->args);
	return (1);
}

void	think(t_philo *philo)
{
	print_state("is thinking", philo);
}

int	routine(t_philo *philo)
{
	if (philo->args->nb_philo == 1)
		return (only_one_philo(philo));
	while (1)
	{
		take_fork(philo);
		take_fork(philo);
		print_state("is eating", philo);
		sem_wait(philo->check_meal_sem);
		philo->last_meal = timestamp();
		philo->eat_count += 1;
		sem_post(philo->check_meal_sem);
		ft_sleep(philo->time_to_eat, philo->args);
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
	while (i < args->nb_philo)
	{
		args->philos[i].pid = fork();
		if (args->philos[i].pid == 0)
		{
			args->philos[i].last_meal = timestamp();
			return (routine(&args->philos[i]));
		}
		i++;
	}
	//pthread_create(&args->death_thread, NULL, &death, args);
	//pthread_detach(args->death_thread);
	//pthread_join(args->death_thread, NULL);
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
