/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:26:31 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/08 18:53:02 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "philosophers.h"

int	init_mutex(t_mutex *mutex, bool *mutex_destroyed)
{
	if (pthread_mutex_init(mutex, NULL))
	{
		*mutex_destroyed = true;
		return (ERROR);
	}
	else
	{
		*mutex_destroyed = false;
		return (SUCCESS);
	}
}

int	init_mutexes(t_mutex **mutexes, unsigned int mutex_nb)
{
	ssize_t	i;
	bool	err;

	*mutexes = (t_mutex *)malloc(sizeof(t_mutex) * mutex_nb);
	if (!*mutexes)
		return (ERROR);
	err = false;
	i = -1;
	while (++i < mutex_nb && !err)
	{
		if (pthread_mutex_init(&(*mutexes)[i], NULL))
			err = true;
	}
	if (err)
	{
		while (--i > -1)
			pthread_mutex_destroy(&(*mutexes)[i]);
		free(*mutexes);
		*mutexes = NULL;
		return (ERROR);
	}
	return (SUCCESS);
}

int	init_philo(t_parsed_data const *parsed_data, t_prime *prime)
{
	long int	i;
	t_philo		*philo;

	prime->philos = (t_philo *)malloc(sizeof(t_philo) * prime->philo_nb);
	if (!prime->philos)
		return (ERROR);
	i = -1;
	while (++i < prime->philo_nb)
	{
		philo = &prime->philos[i];
		philo->finish = &prime->finish;
		philo->finish_mutex = &prime->finish_mutex;
		philo->forks[i % 2] = &prime->forks[(i + 1) % prime->philo_nb];
		philo->forks[(i + 1) % 2] = &prime->forks[i];
		philo->start_time = prime->start_time;
		philo->last_eating_time = prime->start_time;
		philo->last_eating_time_mutex = &prime->last_eating_time_mutexes[i];
		philo->time_to_die = parsed_data->time_to_die;
		philo->time_to_eat = parsed_data->time_to_eat;
		philo->time_to_sleep = parsed_data->time_to_sleep;
		philo->philo_id = (unsigned int)i;
		philo->remain_eat_nb = parsed_data->eat_nb;
	}
	return (SUCCESS);
}

void	init_prime(t_prime *prime, unsigned int philo_nb)
{
	memset(prime, 0, sizeof(*prime));
	prime->finish_mutex_destroyed = true;
	prime->philo_nb = philo_nb;
	prime->start_time = get_curr_time();
}