/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:42:35 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/14 15:42:15 by hdamitzi         ###   ########.fr       */
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check_death;
}	t_args;

typedef struct s_philo
{
	int				index;
	int				lfork;
	int				rfork;
	int				id;
	int				r_frk_tkn;
	int				l_frk_tkn;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				is_dead;
	int				max_meal;
	long long		last_meal;
	t_args			*args;
	pthread_mutex_t	check_meal_mutex;
}	t_philo;

//utils.c
int			ft_atoi(const char *str);
void		print_state(char *state, t_philo *philo);
long long	timestamp(void);

//threads.c
void		create_threads(t_philo *philo, t_args *args);
void		*routine(void *arg);

//eat.c
void		take_fork(t_philo *philo);
void		release_fork(t_philo *philo);

//sleep.c
void		to_sleep(t_philo *philo);
void		ft_sleep(long long time_to);

//think.c
void		think(t_philo *philo);

//death.c
void		death(t_philo *philo);
int			is_dead(t_args *args);

//init.c
void		parse_args(char **av, t_args *args);
void		init_philo(t_philo **philo, t_args *args);
void		philo_attributes(t_philo *one_philo, int id, t_args *args);

#endif
