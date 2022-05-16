/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:43:14 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/14 13:44:22 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

static char	**malloc_str_arr(size_t nstr, size_t length)
{
	char	**strs;
	size_t	i;

	strs = (char **)malloc(sizeof(char *) * nstr);
	if (!strs)
		return (NULL);
	i = 0;
	while (i < nstr)
	{
		strs[i] = (char *)malloc(sizeof(char) * length);

		i++;
	}
}

static char	**generate_sem_names(const char *sem_default_name, int count)
{
	// char	*sem_name_numbered;
	// char	*str_num;

	// str_num = ft_itoa(number);
	// if (!str_num)
	// 	return (NULL);
	// sem_name_numbered = ft_strjoin(sem_name, str_num);
	// free(str_num);
	// if (!sem_name_numbered)
	// 	return (NULL);
	// return (sem_name_numbered);

	char	**sem_names;
	int		i;

	sem_names = (char **)malloc(sizeof(char *) * count);
	if (!sem_names)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		
	}

}

static void delete_sems(const char *sem_name, int cnt)
{
	char	*sem_numbered_name;

	while (--cnt >= 0)
	{
		
	}
}

int	create_sems(const char *sem_name, int cnt, int value)
{
	int		i;
	char	*sem_numbered_name;
	sem_t	*sem;

	i = -1;
	while (++i < cnt)
	{
		sem_numbered_name = generate_sem_names(sem_name, i);
		if (!sem_numbered_name)
		{
			// TODO
		}
		sem = sem_open(sem_numbered_name, O_CREAT, 0666, value);
		if (sem == SEM_FAILED)
		{
			free(sem_numbered_name);
			// TODO
		}
		// TODO
		sem_close(sem);
	}
	// TODO free
	return (SUCCESS);
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
