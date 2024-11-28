/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:43:41 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/27 16:02:26 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(const char *error)
{
	printf(RED "%s\n" RST, error);
	exit(EXIT_FAILURE);
	return (1);
}

int	check_error(t_data *data)
{
	if (data->philo_num > 200 || data->philo_num == 0 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60
		|| data->temp == 0)
		return (1);
	else
		return (0);
}
void safe_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->datas->start_time_mutex);
	pthread_mutex_lock(&philo->philo_id_mutex);
	printf("%lu %d %s\n", ft_get_time_of_day()
		- philo->datas->start_time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->datas->start_time_mutex);
	pthread_mutex_unlock(&philo->philo_id_mutex);
}