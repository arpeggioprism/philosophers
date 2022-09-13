/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:33:53 by jshin             #+#    #+#             */
/*   Updated: 2022/09/13 21:50:35 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac < 5 || 6 < ac)
		return (printf("invalid argc\n"));
	if (check_argv(ac, av))
		return (0);
	if (ft_allocation(&philo, av))
		return (0);
	if (ft_thread(&philo))
		return (0);
	judge(&philo, 0, 0);
	ft_free(&philo);
	return (0);
}
