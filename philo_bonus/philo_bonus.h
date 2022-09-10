/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:34:17 by jshin             #+#    #+#             */
/*   Updated: 2022/09/10 03:38:48 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_thread
{
	pthread_t		philo;
	long long		time;
	int				i;
	int				n_eat;
	int				eat_flag;
	struct s_philo	*all;
}	t_pthread;

typedef struct s_philo
{
	long long	time;
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_eat;
	int			*pids;
	t_pthread	*philos;
	sem_t		*printf;
	sem_t		*forks;
	sem_t		*time_shield;
	sem_t		*eat_shield;
	sem_t		*must_eat;
}	t_philo;

int			ft_atoi(const char *str);
int			check_argv(int ac, char **av);
int			ft_allocation(t_philo *philo, char **av);
int			*ft_thread(t_philo *philo);
int			ft_exit(t_philo *philo, int *pids, int size);
int			ft_exit2(t_philo *philo, int *pids, int size);
void		func(t_pthread *philo, int *pids);
void		*ft_procces(void *ph);
void		out(t_pthread *philo, char *s, int lamp);
void		ft_sem_init(t_philo *philo);
void		ft_usleep(unsigned long time);
void		ft_free(t_philo *philo, int *pids, int l);
void		ft_last_free(t_philo *philo, int *pids);
void        *check_minimum_meals(void *th);
long long	get_time(void);

#endif
