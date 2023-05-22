/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:56:15 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/22 20:57:22 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int		check_death(t_args *args)
{
	int	ret;

	ret = 0;
	sem_wait(args->check_death_sem);
	ret = args->one_dead;
	sem_post(args->check_death_sem);
	return (ret);
}
