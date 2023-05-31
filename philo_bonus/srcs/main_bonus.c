/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:46:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/31 19:46:54 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	think(t_philo *philo)
{
	int	time_to_think;

	sem_wait(philo->check_meal_sem);
	time_to_think = (philo->args->time_to_die - \
	(timestamp() - philo->last_meal) - philo->args->time_to_eat) / 2;
	sem_post(philo->check_meal_sem);
	if (time_to_think >= 600)
		time_to_think = 200;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	print_state("is thinking", philo);
	ft_sleep(time_to_think);
}

int	routine(t_philo *philo)
{
	sem_wait(philo->check_meal_sem);
	philo->last_meal = timestamp();
	sem_post(philo->check_meal_sem);
	pthread_create(&philo->one_death_thread, NULL, death, philo);
	if (philo->index % 2)
		think(philo);
	while (1)
	{
		if ( philo->args->max_eat > 0 && philo->eat_count >= philo->args->max_eat)
			break ;
		take_fork(philo);
		to_sleep(philo);
		think(philo);
	}
	sem_post(philo->args->stop_sem);
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
	pthread_detach(args->death_thread);
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
