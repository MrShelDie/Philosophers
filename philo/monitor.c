/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:19:06 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/13 20:55:15 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/types.h>

static int	check_philo_death(t_prime *prime, ssize_t i)
{
	long int	curr_time;

	curr_time = get_curr_time();
	pthread_mutex_lock(&prime->last_eating_time_mutexes[i]);
	if (curr_time - prime->philos[i].last_eating_time
		> prime->philos[i].time_to_die)
	{
		pthread_mutex_unlock(&prime->last_eating_time_mutexes[i]);
		pthread_mutex_lock(&prime->finish_mutex);
		if (!prime->finish)
		{
			prime->finish = true;
			pthread_mutex_unlock(&prime->finish_mutex);
			pthread_mutex_lock(&prime->print_mutex);
			printf("%ld %ld died\n", curr_time - prime->start_time, i);
			prime->print = false;
			pthread_mutex_unlock(&prime->print_mutex);
			return (EXIT_THREAD);
		}
		pthread_mutex_unlock(&prime->finish_mutex);
	}
	pthread_mutex_unlock(&prime->last_eating_time_mutexes[i]);
	return (CONTINUE_THREAD);
}

static int	check_all_philos(t_prime *prime)
{
	size_t	end_philo_nb;
	ssize_t	i;

	end_philo_nb = 0;
	i = -1;
	while (++i < prime->philo_nb)
	{
		pthread_mutex_lock(&prime->eat_nb_mutexes[i]);
		if (prime->philos[i].eat_nb == 0)
		{
			end_philo_nb++;
			pthread_mutex_unlock(&prime->eat_nb_mutexes[i]);
			continue ;
		}
		pthread_mutex_unlock(&prime->eat_nb_mutexes[i]);
		if (check_philo_death(prime, i))
			return (EXIT_THREAD);
	}
	if (end_philo_nb == prime->philo_nb)
		return (EXIT_THREAD);
	return (CONTINUE_THREAD);
}

static void	*monitor(void *_arg)
{
	t_prime		*arg;

	arg = (t_prime *)_arg;
	while (true)
	{
		pthread_mutex_lock(&arg->finish_mutex);
		if (arg->finish)
		{
			pthread_mutex_unlock(&arg->finish_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&arg->finish_mutex);
		if (check_all_philos(arg))
			return (NULL);
	}
}

int	start_monitor(t_prime *prime)
{
	if (pthread_create(&prime->monitor, NULL, monitor, prime))
	{
		pthread_mutex_lock(&prime->finish_mutex);
		prime->finish = true;
		pthread_mutex_unlock(&prime->finish_mutex);
		return (ERROR);
	}
	return (SUCCESS);
}
