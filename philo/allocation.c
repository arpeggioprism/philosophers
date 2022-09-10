/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:48:57 by jshin             #+#    #+#             */
/*   Updated: 2022/09/10 21:57:55 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_allocation(t_philo *philo, char **av, int i)
{
	philo->n_philo = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	if (av[5])
		philo->n_eat = ft_atoi(av[5]);
	else
		philo->n_eat = 0;
	philo->t_sleep = ft_atoi(av[4]);
	philo->is_dead = 0;
	philo->philos = malloc(sizeof(t_pthread) * (philo->n_philo));
	if (!philo->philos)
		return (printf("failed to malloc philos\n"), 1);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->n_philo);
	if (!philo->forks)
		return (ft_free_error(philo, "failed to malloc forks\n", -3));
	philo->time = get_time();
	pthread_mutex_init(&philo->dead, NULL);
	while (++i < philo->n_philo)
	{
		if (pthread_mutex_init(&philo->philos[i].time_shield, NULL) != 0)
			return (ft_free_error(philo, "failed to init time_shield\n", -2));
		if (pthread_mutex_init(&philo->philos[i].eat_shield, NULL) != 0)
			return (ft_free_error(philo, "failed to init eat_shield\n", -1));
		if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
			return (ft_free_error(philo, "failed to init forks\n", i));
		philo->philos[i].i = i + 1;
		philo->philos[i].n_eat = ((philo->philos[i].all = philo, 0));
		philo->philos[i].time = philo->time;
		philo->philos[i].eat_flag = 0;
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3));
}

void	out(t_pthread *philo, char *s, int lamp)
{
	// pthread_mutex_lock(&philo->all->dead);
	// if (philo->all->is_dead)
	// 	return ;
	// pthread_mutex_unlock(&philo->all->dead);
	pthread_mutex_lock(&philo->all->printf);
	if (s)
		printf("%lld philo %d %s\n", (get_time() - philo->all->time) \
		, philo->i, s);
	if (lamp)
		pthread_mutex_unlock(&philo->all->printf);
}

void	ft_usleep(unsigned long time)
{
	unsigned long	curr;

	curr = get_time();
	while (get_time() - curr < time)
		usleep(50);
}
