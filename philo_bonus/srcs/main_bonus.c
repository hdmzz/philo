/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:46:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/20 14:33:16 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	routine()
{
	printf("Pid is : %d\n", getpid());
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
			return (routine());
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;

	parse_args(av, &args);
	init_philo(&args);
	create_process(&args);
	// wait_and_end(&args);
	// free_all(&args);
	return (0);
}
