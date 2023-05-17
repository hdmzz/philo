/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:46:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/17 21:47:31 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_args	args;

	if (ac - 1 < 4 || ac - 1 > 5)
		return (0);
	parse_args(av, &args);
	init_philo(&args);
	create_threads(&args);
	wait_and_end(&args);
	free_all(&args);
	return (0);
}
