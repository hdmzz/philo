/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:12:28 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/05/22 20:58:36 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (*s1)
		new[j++] = *s1++;
	while (*s2)
		new[j++] = *s2++;
	new[j] = '\0';
	return (new);
}

void	ft_sleep(long long time_to, t_args*args)
{
	long long	start_time;

	if (!check_death(args))
	{
		start_time = timestamp();
		while ((timestamp() - start_time) < time_to)
		{
			if (check_death(args))//on a recupere 100 ms mais la simulation ne sarrete pas encore
				break ;
			usleep(100);
		}
	}
}
