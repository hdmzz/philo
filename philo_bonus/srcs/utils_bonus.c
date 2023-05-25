/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:06:44 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/22 20:55:50 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
	return (t.tv_sec * 1000LL + t.tv_usec / 1000);
}

void	print_state(char *state, t_philo *philo)
{
	sem_wait(philo->args->print_sem);
	if (check_death(philo->args))
	{
		sem_post(philo->args->print_sem);
		return ;
	}
	printf("%lld ", (timestamp() - philo->args->start_simulation));
	printf("%d ", philo->id);
	printf("%s\n", state);
	sem_post(philo->args->print_sem);
}

static int	ft_numberlen(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	newnmbr;
	long	nbrlen;
	char	*res;

	nbrlen = ft_numberlen(n);
	res = (char *)malloc(sizeof(char) * (nbrlen + 1));
	newnmbr = n;
	if (newnmbr < 0)
		newnmbr *= -1;
	if (!res)
		return (NULL);
	res[nbrlen] = '\0';
	if (newnmbr == 0)
		res[0] = '0';
	else
	{
		while (nbrlen-- && newnmbr != 0)
		{
			res[nbrlen] = (newnmbr % 10) + '0';
			newnmbr = newnmbr / 10;
		}
		if (n < 0)
			res[nbrlen] = '-';
	}
	return (res);
}
