/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:41:47 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/01 15:35:36 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_status(t_data *data)
{
	pthread_mutex_lock(&data->status_mutex);
	if (data->argc == 6 && data->status > data->philos->number_of_meals
		* data->philo_num)
	{
		pthread_mutex_unlock(&data->status_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&data->status_mutex);
		return (1);
	}
}

void	eat(t_philo *philo)
{
	if (get_dead(philo->datas) == 0)
	{
		pthread_mutex_lock(&philo->datas->last_time);
		philo->last_meal_time = ft_get_time_of_day();
		pthread_mutex_unlock(&philo->datas->last_time);
		pthread_mutex_lock(&philo->print);
		printf("%lu %d is eating\n", ft_get_time_of_day()
			- philo->datas->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->print);
		ft_usleep(philo->datas->time_to_eat, philo->datas);
		write_status(philo->datas);
	}
}

void	thinking(t_philo *philo)
{
	if (get_dead(philo->datas) == 0)
	{
		pthread_mutex_lock(&philo->print);
		printf("%lu %d is thinking\n", ft_get_time_of_day()
			- philo->datas->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->print);
	}
}

void	sleeping(t_philo *philo)
{
	if (get_dead(philo->datas) == 0)
	{
		pthread_mutex_lock(&philo->print);
		printf("%lu %d is sleeping\n", ft_get_time_of_day()
			- philo->datas->start_time, philo->philo_id);
		ft_usleep(philo->datas->time_to_sleep, philo->datas);
		pthread_mutex_unlock(&philo->print);
	}
}


void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->philo_id % 2 == 0)
        sleeping(philo);

    while (get_status(philo->datas))
    {
        if (get_dead(philo->datas))
            break;

        thinking(philo);
        pick_up_forks(philo);
        eat(philo);
        put_down_forks(philo);
        sleeping(philo);
    }
    return NULL;
}