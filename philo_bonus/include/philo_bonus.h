/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:42:35 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/20 14:32:15 by hdamitzi         ###   ########.fr       */
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
struct s_args;

typedef struct s_philo
{
	pid_t			pid;
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
}	t_philo;

typedef struct s_args
{
pthread_t	death_thread;
int			nb_philo;
int			time_to_die;
int			time_to_eat;
int			time_to_sleep;
int			one_dead;
long long	start_simulation;
int			max_eat;
t_philo		*philos;
}	t_args;

//main_bonus.c

//init.c
void	parse_args(char **av, t_args *args);
void	init_philo(t_args *args);

//utils_bonus.c
void	print_state(char *state, t_philo *philo);
long long	timestamp(void);
int	ft_atoi(const char *str);

#endif
