/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:33:53 by jshin             #+#    #+#             */
/*   Updated: 2022/09/10 22:01:38 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac < 5 || 6 < ac)
		return (printf("invalid argc\n"), 0);
	if (check_argv(ac, av))
		return (0);
	if (ft_allocation(&philo, av, -1))
		return (0);
	if (ft_thread(&philo))
		return (0);
	judge(&philo);
	ft_free(&philo);     
	return (0);
}