/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:48:57 by jshin             #+#    #+#             */
/*   Updated: 2022/09/10 02:40:41 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_allocation(t_philo *philo, char **av)
{
	int	i;

	i = -1;
	philo->n_philo = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->n_eat = ft_atoi(av[5]);
	philo->philos = malloc(sizeof(t_pthread) * (philo->n_philo));
	if (!philo->philos)
		return (0);
	philo->time = get_time();
	while (++i < philo->n_philo)
	{
		philo->philos[i].i = i + 1;
		philo->philos[i].time = philo->time;
		philo->philos[i].n_eat = 0;
		philo->philos[i].eat_flag = 0;
		philo->philos[i].all = philo;
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3));
}

void	ft_usleep(unsigned long time)
{
	unsigned long	curr;

	curr = get_time();
	while (get_time() - curr < time)
		usleep(50);
}

void	ft_sem_init(t_philo *philo)
{
	sem_unlink("forks");
	sem_unlink("printf");
	sem_unlink("time_shield");
	sem_unlink("eat_shield");
	sem_unlink("must_eat");
	philo->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, philo->n_philo);
	philo->printf = sem_open("printf", O_CREAT | O_EXCL, 0644, 1);
	philo->must_eat = sem_open("must_eat", O_CREAT | O_EXCL, 0644, philo->n_philo - 1);
	philo->time_shield = sem_open("time_shield", O_CREAT | O_EXCL, 0644, 1);
	philo->eat_shield = sem_open("eat_shield", O_CREAT | O_EXCL, 0644, 1);
	if (philo->forks == SEM_FAILED || philo->printf == SEM_FAILED || \
	philo->must_eat == SEM_FAILED || philo->time_shield == SEM_FAILED || \
	philo->eat_shield == SEM_FAILED)
	{
		free(philo->philos);
		exit(0);
	}
}
