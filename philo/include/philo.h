#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
//cette structure sera utilise ds une liste mais pas chainee
//donc on utilisera les doule pointeurs je pense
typedef struct s_philo
{
	pthread_t	thread;
	int			nbr_of_philos;
	int			id;
	int			r_fork;
	int			l_fork;
} t_philo;

typedef struct s_fork
{
	int	is_used;
	pthread_mutex_t	lock;
} t_fork;

//main.c
void*	routine(void *philo);
int	ft_atoi(const char *str);
void	init_philo_attributes(t_philo *one_philo, int id);
void	init_philo(t_philo **philo, int nbrs_of_philo);

//threads.c
void	create_threads(t_philo **philo, int nbrs_of_philo);
void	philo_join(t_philo **philo, int nbrs_of_philo);

#endif
