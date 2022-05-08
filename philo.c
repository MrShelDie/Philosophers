/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:36:32 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/08 19:29:00 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo(void *_arg)
{
	t_philo	*arg;

	arg = (t_philo *)_arg;
	if (arg->remain_eat_nb)
	while
	(
		!philo_think(arg)
		&& !philo_take_fork(arg, arg->forks[0])
		&& !philo_take_fork(arg, arg->forks[1])
		&& !philo_put_fork(arg->forks[1])
		&& !philo_put_fork(arg->forks[0])
		&& !philo_eat(arg)
		&& !philo_sleep(arg)
	);
	return (NULL);
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
	if (create_filos(prime, 1, 2))
		return (ERROR);
	return (SUCCESS);
}
