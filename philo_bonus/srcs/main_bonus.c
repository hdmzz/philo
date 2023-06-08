/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:46:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/09 00:21:10 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_philos(t_args *args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (i < args->nb_philo)
	{
		if (args->philos[i] != NULL)
		{
			if (args->philos[i]->check_meal_sem)
				sem_close(args->philos[i]->check_meal_sem);
			free(args->philos[i]);
		}
		i++;
	}
	if (args->philos)
		free(args->philos);
}

int	free_all(t_args *args)
{
	pthread_join(args->death_thread, NULL);
	pthread_join(args->max_meal_thread, NULL);
	sem_close(args->print_sem);
	sem_close(args->check_death_sem);
	sem_close(args->forks_sem);
	sem_close(args->stop_sem);
	sem_close(args->full_philo_sem);
	free_philos(args);
	free(args);
	return (1);
}

int	main(int ac, char **av)
{
	t_args	*args;

	if (ac - 1 < 4 || ac - 1 > 5)
		return (1);
	args = parse_args(ac, av);
	create_process(args);
	if (wait_and_end(args))
		return (free_all(args));
	free_all(args);
	return (0);
}
