/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:00:55 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/27 16:03:46 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_forks(t_philo *philo)
{
	if ((pthread_mutex_lock(&(philo->right_fork->fork)) == 0)
		&& (get_dead(philo->datas) == 0))
	{
		pthread_mutex_lock(&philo->print);
		if (get_status(philo->datas))
			safe_printf(philo, "taken a fork ");
		pthread_mutex_unlock(&philo->print);
	}
	if (philo->datas->philo_num == 1)
	{
		ft_usleep(philo->datas->time_to_die, philo->datas);
		return (1);
	}
	else if ((pthread_mutex_lock(&(philo->left_fork->fork)) == 0)
		&& (get_dead(philo->datas)) == 0)
	{
		pthread_mutex_lock(&philo->print);
		if (get_status(philo->datas))
			safe_printf(philo, "taken a fork ");
		pthread_mutex_unlock(&philo->print);
	}
	return (0);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}
