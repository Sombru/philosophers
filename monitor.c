/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:01:40 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/27 16:04:10 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_data *data)
{
	pthread_mutex_lock(&data->status_mutex);
	data->status++;
	pthread_mutex_unlock(&data->status_mutex);
}

int	get_dead(t_data *data)
{
	int	is_dead;

	pthread_mutex_lock(&data->dead_mutex);
	is_dead = data->dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (is_dead);
}

int	monitor(t_data *data)
{
	int				i;
	unsigned long	last_meal_t;

	i = 0;
	while (i < data->philo_num)
	{
		if ((get_status(data) == 0))
			return (2);
		pthread_mutex_lock(&data->last_time);
		last_meal_t = data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->last_time);
		if (ft_get_time_of_day() - last_meal_t >= data->time_to_die)
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->dead = 1;
			safe_printf(data->philos, "died ");
			pthread_mutex_unlock(&data->dead_mutex);
			destroy(data);
			error_exit(RED "Philospher died, simulation stop\n" RST);
			return (0);
		}
		i++;
	}
	return (1);
}
