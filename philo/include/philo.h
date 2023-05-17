/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:42:35 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/17 12:42:53 by hdamitzi         ###   ########.fr       */
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

struct s_args;

typedef struct s_philo
{
	pthread_t		thrd;
	int				index;
	int				rfork;
	int				lfork;
	int				first;
	int				second;
	int				first_taken;
	int				second_taken;
	int				id;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				is_dead;
	int				max_meal;
	long long		last_meal;
	struct s_args	*args;
	pthread_mutex_t	check_meal_mutex;
}	t_philo;

typedef struct s_args
{
	pthread_t		death_thread;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				one_dead;//stop flag
	long long		start_simulation;
	int				max_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check_death;
	t_philo			*philos;
}	t_args;

//utils.c
int			ft_atoi(const char *str);
void		print_state(char *state, t_philo *philo);
long long	timestamp(void);

//threads.c
void		create_threads(t_args *args);
void		*routine(void *arg);
void		wait_and_end(t_args *args);

//eat.c
void		take_fork(t_philo *philo);
void		release_fork(t_philo *philo);

//sleep.c
void		to_sleep(t_philo *philo);
void		ft_sleep(long long time_to, t_args *args);

//think.c
void		think(t_philo *philo);

//death.c
void		*death(void *a);
int			check_death(t_args *args);

//init.c
void		parse_args(char **av, t_args *args);
void		init_philo(t_args *args);
void		philo_attributes(t_philo *philo, int id, t_args *args);

#endif
