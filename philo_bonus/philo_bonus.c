/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:33:53 by jshin             #+#    #+#             */
/*   Updated: 2022/09/10 03:57:04 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void        *check_minimum_meals(void *th)
{
    int		i;
    t_philo	*philo;
 
    philo = (t_philo *)th;
    i = -1;
    while (i++ < philo->n_philo)
        sem_wait(philo->must_eat);
	sem_wait(philo->must_eat);
	sem_wait(philo->printf);
    printf("%lld every philosopher ate minimum amount of meals\n", get_time() - philo->time);
	ft_exit2(philo, philo->pids, 0);
	return philo;
}

int	main(int ac, char **av)
{
	t_philo	philo;
	int		*pids;

	if (ac < 5 || 6 < ac)
		return (printf("invalid argc\n"), 0);
	check_argv(ac, av);
	if (!ft_allocation(&philo, av))
		return (printf("failed to allocate\n"), 0);
	pids = ft_thread(&philo);
	ft_exit(&philo, pids, 0);
	return (0);
}
