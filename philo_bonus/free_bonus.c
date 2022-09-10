/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:46:38 by jshin             #+#    #+#             */
/*   Updated: 2022/09/10 02:40:42 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free(t_philo *philo, int *pids, int l)
{
	free(pids);
	free(philo->philos);
	exit(l);
}

void	ft_last_free(t_philo *philo, int *pids)
{
	free(pids);
	free(philo->philos);
}
