/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:53:10 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/09 22:29:42 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (res != (((res * 10) + (*str - 48)) / 10))
			return (((sign + 1) / -2));
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000LL) + (t.tv_usec + 1000));
}

void	print_state(char *state, t_philo *philo)
{
	long long	cur_time;

	cur_time = timestamp();
	cur_time -= philo->args->start_simulation;
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%lld %d %s\n", cur_time, philo->id, state);
	pthread_mutex_unlock(&philo->args->print_mutex);
}
