/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:09:28 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/07 20:41:32 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>

# define ERROR 1
# define SUCCESS 0

# define EXIT_THREAD 1
# define CONTINUE_THREAD 0

# define UNDEF_EAT_NB -1
# define ARGC_WITHOUT_EAT_NB 5
# define ARGC_WITH_EAT_NB 6

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_parser_data
{
	unsigned int	philo_nb;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long int		eat_nb;
}	t_parsed_data;

typedef struct s_philo
{
	bool			*finish;
	t_mutex			*finish_mutex;
	t_mutex			*print_mutex;
	t_mutex			*forks[2];
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	philo_id;
	long int		last_eating_time;
	long int		remain_eat_nb;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_prime
{
	bool			finish;
	bool			finish_mutex_destroyed;
	bool			print_mutex_destroyed;
	t_mutex			finish_mutex;
	t_mutex			print_mutex;
	t_mutex			*forks;
	t_mutex			*last_eating_time_mutexes;
	t_philo			*philos;
	unsigned int	philo_nb;
}	t_prime;

unsigned int	ft_atoui(const char *str, bool *err);
int				delay(unsigned int ms);

#endif
