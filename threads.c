/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:46:30 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/13 13:15:10 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time_of_day();
	data->philos->thread = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->philos->thread)
		return ;
	while (i < data->philo_num)
	{
		data->philos[i].last_meal_time = data->start_time;
		pthread_create(&data->philos->thread[i], NULL, &routine,
			&data->philos[i]);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philos->thread[i], NULL);
		i++;
	}
}

void	destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philos->thread[i], NULL);
		i++;
	}
	if (data->philos->thread)
	{
		free(data->philos->thread);
		data->philos->thread = NULL;
	}
	pthread_mutex_destroy(&data->last_time);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->tte);
	pthread_mutex_destroy(&data->sleep);
	pthread_mutex_destroy(&data->status_mutex);
	pthread_mutex_destroy(&data->philos->meal);
	pthread_mutex_destroy(&data->philos->print);
	pthread_mutex_destroy(&data->philos->waiter);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
}
