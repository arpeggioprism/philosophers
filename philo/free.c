/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 02:42:24 by jshin             #+#    #+#             */
/*   Updated: 2022/09/10 21:46:23 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n_philo)
	{
		pthread_mutex_destroy(&(philo->forks[i]));
		pthread_mutex_destroy(&philo->philos[i].time_shield);
		pthread_mutex_destroy(&philo->philos[i].eat_shield);
	}
	pthread_mutex_destroy(&(philo->printf));
	free(philo->philos);
	free(philo->forks);
	return (0);
}

int	ft_free_error(t_philo *philo, char *s, int i)
{
	int	len;
	int	j;

	len = 0;
	while (s[len])
		len++;
	if (i >= -3)
		free(philo->philos);
	if (i >= -2)
		free(philo->forks);
	if (i >= 1)
	{
		j = -1;
		while (++j < philo->n_philo)
		{
			pthread_mutex_destroy(&philo->philos[j].time_shield);
			pthread_mutex_destroy(&philo->philos[j].eat_shield);
			pthread_mutex_destroy(&(philo->forks[j]));
		}
	}
	write(2, s, len);
	return (1);
}
