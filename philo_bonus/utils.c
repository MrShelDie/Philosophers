/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:43:14 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/17 15:40:46 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void	free_strs(char **strs, size_t nstr)
{
	size_t	i;

	i = -1;
	while (++i < nstr)
		free(strs[i]);
	free(strs);
}

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
		usleep(600);
}

void	print_msg(t_prime *prime, const char *msg)
{
	sem_wait(prime->sem_print);
	printf("%ld %d %s",
		get_curr_time() - prime->start_time, prime->philo_id, msg);
	sem_post(prime->sem_print);
}
