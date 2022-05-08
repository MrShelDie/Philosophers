/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:19:06 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/08 19:50:19 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philosophers.h"

static int	check_all_filo(t_prime *prime)
{
	ssize_t		i;
	long int	curr_time;

	i = -1;
	while (++i < prime->philo_nb)
	{
		pthread_mutex_lock(&prime->last_eating_time_mutexes[i]);
		pthread_mutex_lock(&prime->finish_mutex);
		curr_time = get_curr_time();
		if (curr_time - prime->philos[i].last_eating_time
			> prime->philos[i].time_to_die)
		{
			if (!prime->finish)
			{
				prime->finish = true;
				printf("%ld %ld died\n", curr_time - prime->start_time, i);
				pthread_mutex_unlock(&prime->last_eating_time_mutexes[i]);
				pthread_mutex_unlock(&prime->finish_mutex);
				return (EXIT_THREAD);
			}
		}
		pthread_mutex_unlock(&prime->finish_mutex);
		pthread_mutex_unlock(&prime->last_eating_time_mutexes[i]);
	}
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
		if (check_all_filo(arg))
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
