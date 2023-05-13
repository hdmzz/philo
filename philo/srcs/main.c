/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:55:24 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/13 15:50:57 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_args	args;

	if (ac == 5 || ac == 4)
	{
		parse_args(av, &args);
		init_philo(&philo, &args);
		create_threads(philo, &args);
		while(1)
			;
	}
	return (0);
}
