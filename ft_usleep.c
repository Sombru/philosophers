/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:26:05 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/13 13:31:10 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time_of_day(void)
{
	unsigned long	milliseconds;
	struct timeval	time;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

void	ft_usleep(unsigned long duration_ms, t_data *data)
{
	unsigned long	start_time;
	unsigned long	current_time;

	start_time = ft_get_time_of_day();
	while (1)
	{
		current_time = ft_get_time_of_day();
		if ((current_time - start_time) >= duration_ms || get_status(data) == 0)
			break ;
		usleep(1000);
	}
}
