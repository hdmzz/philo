/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:42:35 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/24 15:05:05 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

struct	s_args;

typedef struct s_philo
{
	pid_t			pid;
	pthread_t		one_death_thread;
	char			*meal_sem_name;
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
	int				eat_count;
	long long		last_meal;
	struct s_args	*args;
	sem_t			*check_meal_sem;
}	t_philo;

typedef struct s_args
{
	pthread_t	death_thread;
	sem_t		*stop_sem;
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			one_dead;
	long long	start_simulation;
	int			max_eat;
	t_philo		*philos;
	sem_t		*forks_sem;
	sem_t		*print_sem;
	sem_t		*check_death_sem;
}	t_args;

//main_bonus.c

//init_bonus.c
int			parse_args(int ac, char **av, t_args *args);
void		init_philo(t_args *args);

//utils_bonus.c
void		print_state(char *state, t_philo *philo);
long long	timestamp(void);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);

//utils2_bonus.c
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_sleep(long long time_to, t_args*args);

//death_bonus.c
void		*death(void *a);
int			check_death(t_args *args);
void		stop_simulation(t_args *args);
void		*global_death(void *a);

//fork_bonus.c
void		take_fork(t_philo *philo);
void		release_fork(t_philo *philo);

//sleep_bonus.c
void		to_sleep(t_philo *philo);

#endif
