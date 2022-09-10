/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:34:17 by jshin             #+#    #+#             */
/*   Updated: 2022/09/10 23:33:33 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_thread
{
	pthread_t		philo;
	long long		time;
	int				i;
	int				n_eat;
	int				eat_flag;
	struct s_philo	*all;
	pthread_mutex_t	time_shield;
	pthread_mutex_t	eat_shield;
}	t_pthread;

typedef struct s_philo
{
	int				lamp;
	long long		time;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				is_dead;
	t_pthread		*philos;
	pthread_mutex_t	dead;
	pthread_mutex_t	printf;
	pthread_mutex_t	*forks;
}	t_philo;

int			ft_atoi(const char *str);
int			check_argv(int ac, char **av);
int			ft_allocation(t_philo *philo, char **av, int i);
int			ft_thread(t_philo *philo);
int			ft_free(t_philo *pilo);
int			ft_free_error(t_philo *philo, char *s, int i);
int			n_eat(int *eat_count, t_pthread *philo);
int			ft_allocation_util(t_philo *philo);
void		*judge(t_philo *philo, int i, int eat_count);
void		check_lamp(int ac, t_philo *philo);
void		out(t_pthread *philo, char *s, int lamp);
void		ft_usleep(unsigned long time);
long long	get_time(void);

#endif
