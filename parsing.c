/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:58:21 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/27 10:52:37 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void static	is_valid_input(t_data *data)
{
	if (data->philo_num <= 0)
		error_exit(RED "Atleast one philosopher expected\n" RST);
	if (data->philo_num >= 200)
	{
		printf(Y "WARNING simulating with more than 200 philosophers "
			"may lead to unexpected behaviour\n" RST);
		usleep(996969);
	}
	if (data->time_to_die <= 60 || data->time_to_eat <= 60
		|| data->time_to_sleep <= 60)
		error_exit(RED "Use timestamps greater than " C "60ms\n" RST);
	if (data->time_to_die >= 2147483647 || data->time_to_eat >= 2147483647
		|| data->time_to_sleep >= 2147483647)
		error_exit(RED "Use timestamps less than " C "2147483647ms\n" RST);
}

int	arg_check(char *str, t_data *data)
{
	int	i;
	int	minus;
	int	plus;

	i = 0;
	minus = 0;
	plus = 0;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		else if (str[i] == '+')
			plus++;
		i++;
	}
	if (minus > 0 || plus > 1 || !(str[i] >= '0' && str[i] <= '9'))
	{
		data->check_error++;
		return (0);
	}
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		data->check_error++;
	return (1);
}

long	ft_atoi(char *str)
{
	int		sign;
	long	number;
	int		length;

	sign = 1;
	number = 0;
	length = 0;
	while (*str == ' ' || *str == '\t' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
		length++;
		if (length >= 10)
			error_exit(RED "Number is too big\n" RST);
	}
	return (number * sign);
}

int	parse_input(char **str, t_data *data)
{
	int	i;

	i = 1;
	data->temp = -1;
	data->check_error = 0;
	if (!arg_check(str[i], data))
		return (1);
	data->philo_num = ft_atoi(str[i++]);
	if (!arg_check(str[i], data))
		return (1);
	data->time_to_die = ft_atoi(str[i++]);
	if (!arg_check(str[i], data))
		return (1);
	data->time_to_eat = ft_atoi(str[i++]);
	if (!arg_check(str[i], data))
		return (1);
	data->time_to_sleep = ft_atoi(str[i++]);
	if (str[i] != NULL)
	{
		if (!arg_check(str[i], data))
			return (1);
		data->temp = ft_atoi(str[i++]);
	}
	is_valid_input(data);
	return (data->check_error > 0);
}

int	is_even(t_data *data)
{
	if (data->philo_num % 2 == 0)
		return (2);
	else
		return (1);
}
