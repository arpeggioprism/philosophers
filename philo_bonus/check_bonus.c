/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:37:37 by jshin             #+#    #+#             */
/*   Updated: 2022/09/10 02:40:42 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		r *= 10;
		r += str[i] - 48;
		i++;
	}
	return (r);
}

int	check_argv(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (ft_atoi(av[i]) < 1)
		{
			printf("Error in parsing the input\n");
			exit(0);
		}
	}
	return (0);
}

void	out(t_pthread *philo, char *s, int lamp)
{
	sem_wait(philo->all->printf);
	printf("%lld philo %d %s\n", (get_time() - philo->all->time), philo->i, s);
	if (lamp)
		sem_post(philo->all->printf);
}
