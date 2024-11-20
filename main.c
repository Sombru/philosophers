/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:32:49 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/20 12:20:33 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		data.argc = argc;
		if (parse_input(argv, &data) == 1)
			error_exit(RED "Invalid input\n" RST);
		if (init(&data) == 1)
		{
			destroy(&data);
			error_exit(RED "ERROR, could not initialise data\n" RST);
		}
		create_threads(&data);
		while (1)
		{
			if (get_status(&data) == 0)
				break ;
			if (monitor(&data) == 0)
				break ;
		}
		destroy(&data);
	}
	else
		error_exit(RED "Wrong input:\n" G "Correct format:" ERR ERR2);
}
