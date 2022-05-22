/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:08:29 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/22 13:28:13 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void	free_philo_proc_data(t_prime *prime)
{
	if (prime->sem_group_let)
		free(prime->sem_group_let);
	if (prime->sem_group_kill)
		free(prime->sem_group_kill);
	if (prime->unames_let)
		free_strs(prime->unames_let, prime->n_philo);
	if (prime->unames_kill)
		free_strs(prime->unames_kill, prime->n_philo);
	if (prime->pids_philo)
		free(prime->pids_philo);
}

static void	*monitor(void *arg)
{
	long int	curr_time;
	t_prime		*prime;

	prime = (t_prime *)arg;
	while (1)
	{
		sem_wait(prime->sem_group_let[prime->philo_id]);
		curr_time = get_curr_time();
		if (curr_time - prime->last_eating_time > prime->time_to_die)
		{
			sem_wait(prime->sem_print);
			printf("%ld %d died\n",
				curr_time - prime->start_time, prime->philo_id);
			sem_post(prime->sem_group_let[prime->philo_id]);
			sem_wait(prime->sem_group_kill[prime->philo_id]);
			sem_post(prime->sem_group_kill[prime->philo_id]);
			free_philo_proc_data(prime);
			exit(EXIT_FAILURE);
		}
		sem_post(prime->sem_group_let[prime->philo_id]);
		usleep(1000);
	}
	return (NULL);
}

static void	philo(t_prime *prime)
{
	pthread_t	thread_monitor;

	sem_wait(prime->sem_group_kill[prime->philo_id]);
	if (pthread_create(&thread_monitor, NULL, monitor, prime))
	{
		sem_wait(prime->sem_print);
		write(STDERR_FILENO, "\nInit error\n", 12);
		free_philo_proc_data(prime);
		exit(EXIT_FAILURE);
	}
	pthread_detach(thread_monitor);
	sem_post(prime->sem_group_kill[prime->philo_id]);
	while (prime->n_eat != 0)
	{
		philo_eat(prime);
		philo_sleep(prime);
		philo_think(prime);
	}
	free_philo_proc_data(prime);
	exit(EXIT_SUCCESS);
}

void	wait_philos(t_prime *prime)
{
	int		exit_status;
	ssize_t	i;

	if (!prime->pids_philo || prime->n_created_philo == 0)
		return ;
	waitpid(-1, &exit_status, 0);
	if (exit_status != EXIT_SUCCESS)
	{
		kill_all(prime->pids_philo, prime->n_created_philo,
			prime->sem_group_kill);
		wait_remain(1, prime->n_created_philo);
		return ;
	}
	i = 0;
	while (++i < prime->n_created_philo)
	{
		waitpid(-1, &exit_status, 0);
		if (exit_status != EXIT_SUCCESS)
		{
			kill_all(prime->pids_philo, prime->n_created_philo,
				prime->sem_group_kill);
			wait_remain(i + 1, prime->n_created_philo);
			return ;
		}
	}
}

int	create_philos(t_prime *prime)
{
	size_t	i;

	prime->pids_philo = (pid_t *)malloc(sizeof(pid_t) * prime->n_philo);
	if (!prime->pids_philo)
		return (ERROR);
	prime->start_time = get_curr_time();
	prime->last_eating_time = prime->start_time;
	i = -1;
	while (++i < (size_t)prime->n_philo)
	{
		prime->n_created_philo++;
		prime->philo_id = i;
		prime->pids_philo[i] = fork();
		if (prime->pids_philo[i] == -1)
			return (ERROR);
		else if (prime->pids_philo[i] == 0)
			philo(prime);
	}
	return (SUCCESS);
}
