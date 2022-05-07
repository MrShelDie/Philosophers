/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:36:32 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/07 20:49:16 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	think(t_philo *arg)
{
	pthread_mutex_lock(arg->finish_mutex);
	if (arg->finish)
	{
		pthread_mutex_unlock(arg->finish_mutex);
		return (EXIT_THREAD);
	}
	pthread_mutex_lock(arg->print_mutex);
	// write thinking
	pthread_mutex_unlock(arg->print_mutex);
	pthread_mutex_unlock(arg->finish_mutex);
	return (CONTINUE_THREAD);
}

static int	take_fork(t_philo *arg, t_mutex *fork)
{
	pthread_mutex_lock(arg->finish_mutex);
	if (arg->finish)
	{
		pthread_mutex_unlock(arg->finish_mutex);
		return (EXIT_THREAD);
	}
	pthread_mutex_lock(fork);
	pthread_mutex_lock(arg->print_mutex);
	// write fork
	pthread_mutex_unlock(arg->print_mutex);
	pthread_mutex_unlock(arg->finish_mutex);
	return (CONTINUE_THREAD);
}

static int	eat(t_philo *arg)
{
	pthread_mutex_lock(arg->finish_mutex);
	if (arg->finish)
	{
		pthread_mutex_unlock(arg->finish_mutex);
		return (EXIT_THREAD);
	}
	pthread_mutex_lock(arg->print_mutex);
	// write eating
	pthread_mutex_unlock(arg->print_mutex);

	// last eating time
	// eat_nb--

	pthread_mutex_unlock(arg->finish_mutex);
	if (delay(arg->time_to_eat))
	{
		pthread_mutex_lock(arg->finish_mutex);
		arg->finish = true;
		pthread_mutex_unlock(arg->finish_mutex);
		return (EXIT_THREAD);
	}
	return (CONTINUE_THREAD);
}

static int	sleep(t_philo *arg)
{
	pthread_mutex_lock(arg->finish_mutex);
	if (arg->finish)
	{
		pthread_mutex_unlock(arg->finish_mutex);
		return (EXIT_THREAD);
	}
	pthread_mutex_lock(arg->print_mutex);
	// write sleeping
	pthread_mutex_unlock(arg->print_mutex);
	pthread_mutex_unlock(arg->finish_mutex);
	if (delay(arg->time_to_sleep))
	{
		pthread_mutex_lock(arg->finish_mutex);
		arg->finish = true;
		pthread_mutex_unlock(arg->finish_mutex);
		return (EXIT_THREAD);
	}
	return (CONTINUE_THREAD);
}

void	*philo(void *_arg)
{
	t_philo	*arg;

	arg = (t_philo *)_arg;
	while (1)
	{
		if (think(arg))
			break ;
		if (take_fork(arg, arg->forks[0]))
			break ;
		if (take_fork(arg, arg->forks[1]))
			break ;
		if (eat(arg))
			break ;
		if (sleep(arg))
			break ;
	}
}
