/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:55:24 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/04/24 11:46:08 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *)philo;
	printf("hello philo numero %d\nlfork nbr %p\n rfork nbr %p\n\n", \
	phil->id, phil->l_fork, phil->r_fork);
	return (0);
}

//fonction qui malloc le nombre de fourchette eet qui met tout a 0
void	init_forks(t_fork **forks, int nbrs_of_philo)
{
	int	i;

	i = 0;
	*forks = malloc(sizeof(t_fork) * nbrs_of_philo);
	if (!(*forks))
		exit(EXIT_FAILURE);
	while (i < nbrs_of_philo)
	{
		(*forks)[i].is_used = 0;
		i++;
	}
}

//on attribue a chaque philosophe la fourchette
// qui correspond a leur numero
//fourchettes a droite et pour la gauche on
// prend la fourchette a l index n + 1 de
//notre position
void	philo_attributes(t_philo *one_philo, t_fork **forks, int id, int nbrs)
{
	one_philo->id = id;
	one_philo->r_fork = &((*forks)[id]);
	if (id == (nbrs - 1))
		one_philo->l_fork = &((*forks)[0]);
	else
		one_philo->l_fork = &((*forks)[id + 1]);
}

void	init_philo(t_philo **philo, t_fork **forks, int nbrs_of_philo)
{
	int	i;

	i = -1;
	*philo = malloc(sizeof(t_philo) * nbrs_of_philo);
	if (!(*philo))
		exit(EXIT_FAILURE);
	while (++i < nbrs_of_philo)
		philo_attributes(&(*philo)[i], forks, i, nbrs_of_philo);
}

int	main(int ac, char **av)
{
	t_fork	*forks;
	t_philo	*philo;
	int		nbrs_of_philo;

	if (ac < 2)
		exit(EXIT_FAILURE);
	nbrs_of_philo = ft_atoi(av[1]);
	init_forks(&forks, nbrs_of_philo);
	init_philo(&philo, &forks, ft_atoi(av[1]));
	create_threads(&philo, nbrs_of_philo);
	philo_join(&philo, nbrs_of_philo);
	return (0);
}
