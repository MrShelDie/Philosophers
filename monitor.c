/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:19:06 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/08 19:10:45 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philosophers.h"

static void	*monitor(void *_arg)
{
	t_prime		*arg;
	ssize_t		i;
	long int	curr_time;

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
		i = -1;
		while (++i < arg->philo_nb)
		{
			pthread_mutex_lock(&arg->last_eating_time_mutexes[i]);
			pthread_mutex_lock(&arg->finish_mutex);
			curr_time = get_curr_time();
			if (curr_time - arg->philos[i].last_eating_time
				> arg->philos[i].time_to_die)
			{
				if (!arg->finish)
				{
					arg->finish = true;
					printf("%ld %ld died\n", curr_time - arg->start_time, i);
					pthread_mutex_unlock(&arg->last_eating_time_mutexes[i]);
					pthread_mutex_unlock(&arg->finish_mutex);
					return (NULL);
				}
			}
			pthread_mutex_unlock(&arg->finish_mutex);
			pthread_mutex_unlock(&arg->last_eating_time_mutexes[i]);
		}
	}
	return (NULL);
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
