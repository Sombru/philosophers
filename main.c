/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:32:49 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/01 14:26:40 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		data.argc = argc;
		if (parse_input(argv, &data) == 1)
			return (error_exit("Failure"));
		init(&data);
		create_threads(&data);
		while (1)
		{
			if (get_status(&data) == 0)
				break;
			if (monitor(&data) == 0)
				break;
		}
		join_threads(&data);
		destroy(&data);
	}
	else
		error_exit("Wrong input:\n"
                   G"Correct format: ./philo <number_of_philosophers> <time_to_die> <time_to_sleep> [<number_of_meals>]"RST);
	return (0);
	
}