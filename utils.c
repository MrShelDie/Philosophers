/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:21:20 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/08 17:50:53 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
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
	long int	start_time;
	long int	time_quant;

	start_time = get_curr_time();
	time_quant = ms / 10 + 1;
	while (get_curr_time() - start_time < ms)
		usleep(time_quant);
}

int	print_msg(t_philo *arg, const char *msg)
{
	pthread_mutex_lock(arg->finish_mutex);
	if (*arg->finish)
	{
		pthread_mutex_unlock(arg->finish_mutex);
		return (EXIT_THREAD);
	}
	printf("%ld %u %s", get_curr_time() - arg->start_time, arg->philo_id, msg);
	pthread_mutex_unlock(arg->finish_mutex);
	return (CONTINUE_THREAD);
}
