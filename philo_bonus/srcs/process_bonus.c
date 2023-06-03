/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:05:17 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/02 21:54:43 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	create_process(t_args *args)
{
	int	i;
	pid_t	pid;

	i = 0;
	args->start_simulation = timestamp() + 500;
	sem_wait(args->stop_sem);
	while (i < args->nb_philo)
	{
		pid = fork();
		if (pid > 0)
			args->philos[i]->pid = pid;
		if (args->philos[i]->pid == 0)
			routine(args->philos[i]);
		i++;
	}
	pthread_create(&args->death_thread, NULL, &global_death, (void *)args);
	pthread_create(&args->max_meal_thread, NULL, &are_philo_full, args);
	return (0);
}

void	start_synchro(long long start_time)
{
	while (timestamp() < start_time)
		continue ;
}

int	wait_and_end(t_args *args)
{
	int	i;
	int	ret;

	ret = 1;
	i = 0;
	while (i < args->nb_philo)
	{
		if (waitpid(args->philos[i]->pid, NULL, 0) == -1)
			ret = 0;
		i++;
	}
	return (ret);
}
