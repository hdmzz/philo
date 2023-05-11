/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:42:35 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/11 12:13:01 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	int				is_used;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_args
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				one_dead;
	long long		start_simulation;
	int				max_eat;
	
	pthread_mutex_t	print_mutex;
}	t_args;

typedef struct s_philo
{
	pthread_t		thread;
	int				nbr_of_philos;
	int				id;
	t_fork			*r_fork;
	t_fork			*l_fork;
	int				r_frk_taken;
	int				l_frk_taken;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				is_dead;
	int				max_meal;
	long long		last_meal;
	t_args			*args;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	philmutex;
}	t_philo;

//utils.c
int			ft_atoi(const char *str);
void		print_state(char *state, t_philo *philo);
long long	timestamp(void);

//main.c
void		init_philo(t_philo **philo, t_fork **forks, t_args *args);

//threads.c
void		create_threads(t_philo *philo, t_args *args);
void		philo_join(t_philo **philo, t_args *args);
void		*routine(void *arg);

//eat.c
void		take_fork(char fork_hand, t_philo *philo);
void		release_fork(t_philo *philo);
void		init_forks(t_fork **forks, t_args *args);

//sleep.c
void		to_sleep(t_philo *philo);
void	ft_sleep(long long time_to);

//think.c
void		think(t_philo *philo);

#endif
