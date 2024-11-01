/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:58:21 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/01 13:07:42 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_check(char *str, t_data *data)
{
	int	i;
	int	minus;
	int	plus;

	i = 0;
	minus = 0;
	plus = 0;
	// Check for any signs at the start
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		else if (str[i] == '+')
			plus++;
		i++;
	}
	// If invalid signs or no digits follow the signs, return an error
	if (minus > 0 || plus > 1 || !(str[i] >= '0' && str[i] <= '9'))
	{
		data->check_error++;
		return (0);
	}
	// Check that the remainder is numeric
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	// If there are non-numeric characters, increment error
	if (str[i] != '\0')
		data->check_error++;
	return (1);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	number;

	sign = 1;
	number = 0;
	// Skip whitespace
	while (*str == ' ' || *str == '\t' || (*str >= 9 && *str <= 13))
		str++;
	// Handle sign
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	// Convert number
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
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
	return (data->check_error > 0);
}
