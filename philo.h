/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:28:37 by pkostura          #+#    #+#             */
/*   Updated: 2024/11/01 13:09:11 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <unistd.h> // write, sleep 
#include <stdbool.h> // bool (0,1)
#include <pthread.h> // mutex: init destroy lock unlock
					 //			

#include <sys/time.h> // gettimeofday
#include <limits.h> // int max
#include <errno.h>

#ifndef PHILO_H
#define PHILO_H

// ASCII Escape sequences for Bold Text Colors
// Usage:
// 	printf(R "This is red text." RST);
// 	printf(B "This is blue text." RST);
// Remeber to use RST to reser the color after setting it

# define RST	"\033[0m"		//reset to default color
# define RED	"\033[1;31m"	// bold red
# define G		"\033[1;32m"	// bold green
# define Y		"\033[1;33m"	// bold Yellow
# define B		"\033[1;34m"	// bold blue
# define M		"\033[1;35m"	// bold magenta
# define C		"\033[1;36m"	// bold cyan
# define W		"\033[1;37m"	// bold white

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	pthread_t			*thread;
	pthread_mutex_t		waiter;
	pthread_mutex_t		meal;
	pthread_mutex_t		print;
	int					philo_id;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_data				*datas;
	unsigned long		last_meal_time;
	int					numbers_time_to_eat;
}						t_philo;

typedef struct s_data
{
	t_philo				*philos;
	t_fork				*forks;
	pthread_mutex_t		sleep;
	pthread_mutex_t		last_time;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		tte;
	int					argc;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					temp;
	int					philo_num;
	int					dead;
	unsigned long		start_time;
	pthread_mutex_t		status_mutex;
	int					status;
	int					check_error;
}						t_data;


// prototypes
int 			error_exit(const char *error);
int				check_error(t_data *data);
unsigned long 	ft_get_time_of_day(void);
void			ft_useelp(unsigned long arg, t_data *data);
void			init_mutexes(t_data *data);
int 			init(t_data *data);
int 			pick_up_forks(t_philo *philo);
void			put_down_forks(t_philo *philo);
int 			get_status(t_data *data);
void			eat(t_philo *philo);
void			thinking(t_philo *philo);
void			sleeping(t_philo *philo);
void			*routine(void *arg);
void			create_threads(t_data *data);
void 			join_threads(t_data *data);
void			destroy(t_data *data);
void			write_status(t_data *data);
int				get_dead(t_data *data);
int				monitor(t_data *data);
void			ft_usleep(unsigned long arg, t_data *data);
unsigned long 	ft_get_time_of_day(void);
int 			parse_input(char **str, t_data *data);
int				ft_atoi(char *str);
int				arg_check(char *str, t_data *data);








#endif
