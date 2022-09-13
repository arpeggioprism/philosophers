/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:29:41 by jshin             #+#    #+#             */
/*   Updated: 2022/09/11 03:47:28 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sets_fork(t_pthread *philo, int x)
{
	if (x == 0)
	{
		pthread_mutex_lock(&philo->all->forks[(philo->i - 1)]);
		out(philo, "has taken a fork", 1);
		pthread_mutex_lock(&philo->all->forks[(philo->i)
			% philo->all->n_philo]);
		out(philo, "has taken a fork", 1);
	}
	else
	{
		pthread_mutex_unlock(&philo->all->forks[(philo->i - 1) % \
		philo->all->n_philo]);
		pthread_mutex_unlock(&philo->all->forks[(philo->i) % \
		philo->all->n_philo]);
	}
}

void	*func(void *ph)
{
	t_pthread	*philo;

	philo = ph;
	if (!(philo->i & 1))
		ft_usleep(philo->all->t_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->all->dead);
		if (philo->all->is_dead)
			return (NULL);
		pthread_mutex_unlock(&philo->all->dead);
		sets_fork(philo, 0);
		out(philo, "is eating", 1);
		pthread_mutex_lock(&philo->eat_shield);
		philo->n_eat += 1;
		pthread_mutex_unlock(&philo->eat_shield);
		pthread_mutex_lock(&philo->time_shield);
		philo->time = get_time();
		pthread_mutex_unlock(&philo->time_shield);
		ft_usleep(philo->all->t_eat);
		sets_fork(philo, 1);
		out(philo, "is sleeping", 1);
		ft_usleep(philo->all->t_sleep);
		out(philo, "is thinking", 1);
	}
}

void	*judge(t_philo *philo, int i, int eat_count)
{
	while (1)
	{
		if (i == philo->n_philo)
			i = 0;
		if (philo->n_eat)
		{
			if (!n_eat(&eat_count, &philo->philos[i]))
				return (NULL);
		}
		pthread_mutex_lock(&philo->philos[i].time_shield);
		if ((get_time() - philo->philos[i].time) >= philo->t_die)
		{
			pthread_mutex_unlock(&philo->philos[i].time_shield);
			out(&philo->philos[i], "died", 0);
			pthread_mutex_lock(&philo->dead);
			philo->is_dead = 1;
			pthread_mutex_unlock(&philo->dead);
			usleep(1000000);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->philos[i].time_shield);
		i++;
	}
	return (NULL);
}

int	ft_thread(t_philo *philo)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&philo->printf, NULL) != 0)
		return (ft_free_error(philo, "failed to pthread_mutex_init\n", 2));
	while (++i < philo->n_philo)
	{
		if (pthread_create(&philo->philos[i].philo, NULL, func, \
		&philo->philos[i]) != 0)
		{
			write(2, "failed to pthread_create\n", 25);
			return (1);
		}
		if (pthread_detach(philo->philos[i].philo) != 0)
		{
			write(2, "failed to pthread_detach\n", 25);
			return (1);
		}
	}
	return (0);
}

int	n_eat(int *eat_count, t_pthread *philo)
{
	pthread_mutex_lock(&philo->eat_shield);
	if (philo->eat_flag == 0 && philo->n_eat >= philo->all->n_eat)
	{
		*eat_count += 1;
		philo->eat_flag = 1;
	}
	pthread_mutex_unlock(&philo->eat_shield);
	if (*eat_count >= philo->all->n_philo)
	{
		out(philo, "every philosopher ate minimum amount of meals\n", 0);
		pthread_mutex_lock(&philo->all->dead);
		philo->all->is_dead = 1;
		pthread_mutex_unlock(&philo->all->dead);
		usleep(1000000);
		return (0);
	}
	return (1);
}
