/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:42:35 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/04/24 13:55:42 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				is_used;
	pthread_mutex_t	lock;
}	t_fork;

//cette structure sera utilise ds une liste mais pas chainee
//donc on utilisera les doule pointeurs je pense
typedef struct s_philo
{
	pthread_t		thread;
	int				nbr_of_philos;
	int				id;
	t_fork			*r_fork;
	t_fork			*l_fork;
	int				r_frk_taken;
	int				l_frk_taken;
	int				is_dead;
	int				max_meal;
	pthread_mutex_t	philmutex;
}	t_philo;

//utils.c
int		ft_atoi(const char *str);

//main.c
void	*routine(void *arg);
void	init_philo(t_philo **philo, t_fork **forks, int nbrs_of_philo);

//threads.c
void	create_threads(t_philo **philo, int nbrs_of_philo);
void	philo_join(t_philo **philo, int nbrs_of_philo);

//eat.c
void	philo_eat(t_philo *philo);

#endif
