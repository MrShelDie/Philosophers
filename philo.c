/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:36:32 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/08 02:11:49 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>

#include "philosophers.h"

long int	get_curr_time(void)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ERROR);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	delay(unsigned int ms)
{
	long int	time;
	long int	time_quant;

	time = get_curr_time();
	time_quant = ms / 10 + 1;
	while (time < ms)
	{
		usleep(time_quant);
		time += get_curr_time();
	}
}

int	print_msg(t_philo *arg, const char *msg)
{
	pthread_mutex_lock(arg->finish_mutex);
	if (arg->finish)
	{
		pthread_mutex_unlock(arg->finish_mutex);
		return (EXIT_THREAD);
	}
	pthread_mutex_lock(arg->print_mutex);
	printf("%ld %ud %s", get_curr_time - arg->start_time, arg->philo_id, msg);
	pthread_mutex_unlock(arg->print_mutex);
	pthread_mutex_unlock(arg->finish_mutex);
	return (CONTINUE_THREAD);
}

void	*philo(void *_arg)
{
	t_philo	*arg;

	arg = (t_philo *)_arg;
	while
	(
		!think(arg)
		&& !take_fork(arg, arg->forks[0])
		&& !take_fork(arg, arg->forks[1])
		&& !put_fork(arg, arg->forks[1])
		&& !put_fork(arg, arg->forks[0])
		&& !eat(arg)
		&& !sleep(arg)
	);
}
