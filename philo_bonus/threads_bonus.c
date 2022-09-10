/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 19:29:41 by jshin             #+#    #+#             */
/*   Updated: 2022/09/10 03:57:08 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sets_fork(t_pthread *philo, int x)
{
	if (x == 0)
	{
		sem_wait(philo->all->forks);
		out(philo, "has taken a fork", 1);
		sem_wait(philo->all->forks);
		out(philo, "has taken a fork", 1);
	}
	else
	{
		sem_post(philo->all->forks);
		sem_post(philo->all->forks);
	}
}

void	func(t_pthread *philo, int *pids)
{
	if (pthread_create(&philo->philo, NULL, ft_procces, (void *)philo) != 0)
		ft_free(philo->all, pids, 1);
	if (pthread_detach(philo->philo) != 0)
		ft_free(philo->all, pids, 1);
	while (1)
	{
		if (philo->all->n_eat)
		{
			sem_wait(philo->all->eat_shield);
			if (philo->eat_flag == 0 && philo->n_eat >= philo->all->n_eat)
			{
				philo->eat_flag = 1;
				sem_post(philo->all->must_eat);
			}
			sem_post(philo->all->eat_shield);
		}
		sem_wait(philo->all->time_shield);
		if ((get_time() - philo->time) > philo->all->t_die)
		{
			sem_post(philo->all->time_shield);
			out(philo, "died", 0);
			ft_free(philo->all, pids, 1);
		}
		sem_post(philo->all->time_shield);
		usleep(50);
	}
}

void	*ft_procces(void *ph)
{
	t_pthread	*philo;

	philo = ph;
	if (!(philo->i & 1))
		ft_usleep(philo->all->t_eat / 2);
	while (1)
	{
		sets_fork(philo, 0);
		out(philo, "is eating", 1);
		sem_wait(philo->all->eat_shield);
		philo->n_eat += 1;
		sem_post(philo->all->eat_shield);
		sem_wait(philo->all->time_shield);
		philo->time = get_time();
		sem_post(philo->all->time_shield);
		ft_usleep(philo->all->t_eat);
		sets_fork(philo, 1);
		out(philo, "is sleeping", 1);
		ft_usleep(philo->all->t_sleep);
		out(philo, "is thinking", 1);
	}
}

int	*ft_thread(t_philo *philo)
{
	int	i;
	int	pid;
	int	*pids;
	pthread_t	var_minimum_meals;

	ft_sem_init(philo);
	pids = malloc(sizeof(int) * philo->n_philo);
	if (!pids)
	{
		free(philo->philos);
		write(2, "failed to malloc in ft_thread.\n", 31);
		exit(1);
	}
	if (pthread_create(&var_minimum_meals, NULL, check_minimum_meals, philo) != 0)
		ft_free(philo, pids, 0);
	if (pthread_detach(var_minimum_meals) != 0)
		ft_free(philo, pids, 0);
	i = -1;
	while (++i < philo->n_philo)
	{
		pid = fork();
		if (pid == 0)
			func(&philo->philos[i], pids);
		else
			pids[i] = pid;
	}
	philo->pids = pids;

	return (pids);
}

int	ft_exit(t_philo *philo, int *pids, int size)
{
	int	i;
	int	status;

	if (size == philo->n_philo)
		return (ft_last_free(philo, pids), 0);
	waitpid(-1, &status, 0);
	sem_close(philo->printf);
	sem_close(philo->forks);
	sem_close(philo->time_shield);
	sem_close(philo->eat_shield);
	sem_unlink("printf");
	sem_unlink("forks");
	sem_unlink("time_shield");
	sem_unlink("eat_shield");
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < philo->n_philo)
				kill(pids[i], SIGKILL);
		}
		else
			return (ft_exit(philo, pids, size + 1));
	}
	else
	{
		i = -1;
		while (++i < philo->n_philo)
			kill(pids[i], SIGKILL);
	}
	ft_last_free(philo, pids);
	return (0);
}

int	ft_exit2(t_philo *philo, int *pids, int size)
{
	int	i;
	int	status;

	ft_last_free(philo, pids);
	i = -1;
		while (++i < philo->n_philo)
			kill(pids[i], SIGKILL);
	exit(0);
	i = 0;
	size = 0;
	status = 0;
	printf("i size status: %d %d %d\n", i, size, status);
	return 0;
	// if (size == philo->n_philo)
	// 	return (ft_last_free(philo, pids), 0);
	// if (WIFEXITED(status))
	// {
	// 	if (WEXITSTATUS(status) == 1)
	// 	{
	// 		i = -1;
	// 		while (++i < philo->n_philo)
	// 			kill(pids[i], SIGKILL);
	// 	}
	// 	else
	// 		return (ft_exit(philo, pids, size + 1));
	// }
	// else
	// {
	// 	i = -1;
	// 	while (++i < philo->n_philo)
	// 		kill(pids[i], SIGKILL);
	// }
	// ft_last_free(philo, pids);
	// return (0);
}