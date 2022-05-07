/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:09:28 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/07 15:15:48 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>

# define ERROR 1
# define SUCCESS 0

# define UNDEF_EAT_NB -1

typedef pthread_mutex_t	t_mutex;

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
	t_mutex			*forks[2];
	long int		last_eating_sec;
	long int		last_eating_usec;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long int		remain_eat_nb;
}	t_philo;

typedef struct s_prime
{
	t_mutex			*forks;
	t_philo			*philos;
	unsigned int	philo_nb;
	bool			forks_destroyed;
	bool			finish;
}	t_prime;

unsigned int	ft_atoui(const char *str, bool *err);

#endif
