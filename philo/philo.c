/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:36:32 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/11 20:24:10 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	*philo(void *_arg)
{
	t_philo	*arg;

	arg = (t_philo *)_arg;
	while (1)
	{
		pthread_mutex_lock(arg->finish_mutex);
		if (*arg->finish)
		{
			pthread_mutex_unlock(arg->finish_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(arg->finish_mutex);
		if (arg->eat_nb != UNDEF_EAT_NB && arg->eat_nb <= 0)
			return (NULL);
		philo_take_fork(arg, 0);
		philo_take_fork(arg, 1);
		philo_eat(arg);
		philo_sleep(arg);
		philo_think(arg);
	}
}

static int	create_filos(t_prime *prime, unsigned int start, unsigned int step)
{
	unsigned int	i;

	i = start;
	while (i < prime->philo_nb)
	{
		prime->philos[i].philo_id = i;
		if (pthread_create(
				&prime->philos[i].thread_id, NULL, philo, &prime->philos[i]))
		{
			pthread_mutex_lock(&prime->finish_mutex);
			prime->finish = true;
			pthread_mutex_unlock(&prime->finish_mutex);
			return (ERROR);
		}
		i += step;
	}
	return (SUCCESS);
}

int	start_philo(t_prime *prime)
{
	if (create_filos(prime, 0, 2))
		return (ERROR);
	usleep(5000);
	if (create_filos(prime, 1, 2))
		return (ERROR);
	return (SUCCESS);
}
