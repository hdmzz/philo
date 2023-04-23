/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:55:24 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/04/23 18:48:56 by hdamitzi         ###   ########.fr       */
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

void*	routine(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *)philo;
	printf("hello philo numero %d\n", phil->id);
	return 0;
}

void	init_philo_attributes(t_philo *one_philo, int id)
{
	one_philo->id = id;
}

void	init_philo(t_philo **philo, int nbrs_of_philo)//juste besoin d'un tableau de threads
{
	int	i;

	i = -1;
	*philo = malloc(sizeof(t_philo) * nbrs_of_philo);
	if (!(*philo))
		exit(EXIT_FAILURE);
	while (++i < nbrs_of_philo)
		init_philo_attributes(&(*philo)[i], i);
}

int	main(int ac, char **av) {
	t_philo			*philo;
	pthread_mutex_t		mutex;
	int					nbrs_of_philo;

	if (ac < 2)
		exit(EXIT_FAILURE);
	nbrs_of_philo = ft_atoi(av[1]);
	pthread_mutex_init(&mutex, NULL);
	init_philo(&philo, ft_atoi(av[1]));
	create_threads(&philo, nbrs_of_philo);
	philo_join(&philo, nbrs_of_philo);
	pthread_mutex_destroy(&mutex);
	return 0;
}
