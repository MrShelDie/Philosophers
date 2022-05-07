/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 19:19:06 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/07 19:47:39 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

#include "philosophers.h"

int	start_philo(t_prime *prime)
{
	// TODO philo thread_id
}

int	delay(unsigned int ms)
{
	t_timeval	tv;
	long int	time;
	long int	time_quant;

	if (gettimeofday(&tv, NULL))
		return (ERROR);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	time_quant = ms / 10 + 1;
	while (time < ms)
	{
		usleep(time_quant);
		if (gettimeofday(&tv, NULL))
			return (ERROR);
		time += tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
	return (SUCCESS);
}
