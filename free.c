/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:28:06 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/08 12:41:29 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "philosophers.h"

void	free_mutexes(t_mutex **mutexes, unsigned int mutex_nb)
{
	ssize_t	i;

	if (*mutexes)
	{
		i = -1;
		while (++i < mutex_nb)
			pthread_mutex_destroy(&(*mutexes)[i]);
		free(*mutexes);
		*mutexes = NULL;
	}
}

void	free_prime(t_prime *prime)
{
	free_mutexes(&prime->forks, prime->philo_nb);
	free_mutexes(&prime->last_eating_time_mutexes, prime->philo_nb);
	if (!prime->finish_mutex_destroyed)
		pthread_mutex_destroy(&prime->finish_mutex);
	if (prime->philos)
	{
		free(prime->philos);
		prime->philos = NULL;
	}
}
