/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:43:14 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/22 13:34:08 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long int	get_curr_time(void)
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	delay(unsigned int ms)
{
	long int	start_time;

	start_time = get_curr_time();
	while (get_curr_time() - start_time < ms)
		usleep(500);
}

void	print_msg(t_prime *prime, const char *msg)
{
	sem_wait(prime->sem_print);
	printf("%ld %d %s",
		get_curr_time() - prime->start_time, prime->philo_id, msg);
	sem_post(prime->sem_print);
}
