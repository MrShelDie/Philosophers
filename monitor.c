/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:19:06 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/08 14:33:33 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philosophers.h"

static void	*monitor(void *_arg)
{
	t_prime		*arg;
	ssize_t		i;

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
			if (arg->philos[i].last_eating_time != UNDEF_LAST_EATING_TIME
				&& get_curr_time() - arg->philos[i].last_eating_time
				> arg->philos[i].time_to_eat)
			{
				pthread_mutex_lock(&arg->finish_mutex);
				arg->finish = true;
				printf("%ld %ld died\n", get_curr_time() - arg->start_time, i);
				pthread_mutex_unlock(&arg->finish_mutex);
			}
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
