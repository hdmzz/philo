/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:46:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/22 14:25:31 by hdamitzi         ###   ########.fr       */
=======
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:46:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/24 15:19:06 by hdamitzi         ###   ########.fr       */
>>>>>>> version-ok
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

<<<<<<< HEAD
int	routine(t_philo *philo)
{
	sem_wait(philo->args->testsem);
	printf("sem pris philo %d\n", philo->id);
	sem_post(philo->args->testsem);
=======
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
>>>>>>> version-ok
	return (1);
}

int	create_process(t_args *args)
{
	int	i;

	i = 0;
<<<<<<< HEAD
=======
	args->start_simulation = timestamp();
	sem_wait(args->stop_sem);
>>>>>>> version-ok
	while (i < args->nb_philo)
	{
		args->philos[i].pid = fork();
		if (args->philos[i].pid == 0)
			return (routine(&args->philos[i]));
		i++;
	}
<<<<<<< HEAD
	return (0);
}

int	wait_and_end(t_args *args)//le main proces doit attendre tout les process enfants
=======
	pthread_create(&args->death_thread, NULL, &global_death, args);
	pthread_join(args->death_thread, NULL);
	return (0);
}

int	wait_and_end(t_args *args)
>>>>>>> version-ok
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

<<<<<<< HEAD
	parse_args(av, &args);
	init_philo(&args);
	create_process(&args);
	wait_and_end(&args);
	// free_all(&args);
=======
	if (ac - 1 < 4 || ac - 1 > 5)
		return (1);
	if (!parse_args(ac, av, &args))
		exit(EXIT_FAILURE);
	init_philo(&args);
	create_process(&args);
	wait_and_end(&args);
>>>>>>> version-ok
	return (0);
}
