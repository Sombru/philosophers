/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:29:17 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/13 13:13:40 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	if ((ret = pthread_mutex_init(&data->last_time, NULL)) != 0
		|| (ret = pthread_mutex_init(&data->philos->meal, NULL)) != 0
		|| (ret = pthread_mutex_init(&data->philos->print, NULL)) != 0
		|| (ret = pthread_mutex_init(&data->philos->waiter, NULL)) != 0
		|| (ret = pthread_mutex_init(&data->dead_mutex, NULL)) != 0
		|| (ret = pthread_mutex_init(&data->tte, NULL)) != 0
		|| (ret = pthread_mutex_init(&data->sleep, NULL)) != 0
		|| (ret = pthread_mutex_init(&data->status_mutex, NULL)) != 0)
	{
		error_exit("Error in mutex initialization");
		return ;
	}
	while (i < data->philo_num)
	{
		ret = pthread_mutex_init(&(data->forks[i].fork), NULL);
		if (ret != 0)
		{
			error_exit("Error in fork mutex initialization");
			destroy(data); // Destroy any previously initialized mutexes
			return ;
		}
		i++;
	}
}

int	init(t_data *data)
{
	int i;

	i = 0;
	data->dead = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (!data->forks)
		return (1);
	data->forks = malloc(sizeof(t_fork) * data->philo_num);
	if (!data->forks)
		return (1);
	data->status = 0;
	while (i < data->philo_num)
	{
		data->philos[i].philo_id = i + 1;
		data->forks[i].fork_id = i;
		data->philos[i].right_fork = &data->forks[data->philos[i].philo_id - 1];
		data->philos[i].left_fork = &data->forks[i + 1];
		if (i == data->philo_num - 1)
			data->philos[i].left_fork = &data->forks[0];
		data->philos[i].datas = data;
		data->philos[i].number_of_meals = data->temp;
		i++;
	}
	init_mutexes(data);
	return (0);
}