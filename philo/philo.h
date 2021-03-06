/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:09:28 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/22 13:48:12 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>

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
	bool			*print;
	t_mutex			*finish_mutex;
	t_mutex			*print_mutex;
	t_mutex			*last_eating_time_mutex;
	t_mutex			*eat_nb_mutex;
	t_mutex			*forks[2];
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	philo_id;
	long int		last_eating_time;
	long int		start_time;
	long int		eat_nb;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_prime
{
	bool			finish;
	bool			print;
	bool			finish_mutex_destroyed;
	bool			print_mutex_destroyed;
	t_mutex			finish_mutex;
	t_mutex			print_mutex;
	t_mutex			*forks;
	t_mutex			*last_eating_time_mutexes;
	t_mutex			*eat_nb_mutexes;
	t_philo			*philos;
	unsigned int	philo_nb;
	long int		start_time;
	pthread_t		monitor;
}	t_prime;

unsigned int	atoui(const char *str, bool *err);
long int		get_curr_time(void);
void			delay(unsigned int ms);
void			print_msg(t_philo *arg, const char *msg);

void			philo_think(t_philo *arg);
void			philo_take_fork(t_philo *arg, unsigned int fork_num);
void			philo_eat(t_philo *arg);
void			philo_sleep(t_philo *arg);

int				start_philo(t_prime *prime);
int				start_monitor(t_prime *prime);

int				init_prime(t_parsed_data const *parsed_data, t_prime *prime);
int				init_mutex(t_mutex *mutex, bool *mutex_destroyed);
int				init_mutexes(t_mutex **mutexes, unsigned int mutex_nb);
int				init_philos(t_parsed_data const *parsed_data, t_prime *prime);

void			free_prime(t_prime *prime);
void			free_mutexes(t_mutex **mutexes, unsigned int mutex_nb);

#endif
