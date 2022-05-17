/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:08:29 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/17 19:39:59 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void	free_philo_proc_data(t_prime *prime)
{
	if (prime->unique_names_last_eating_time
		&& prime->sem_group_last_eating_time
	)
		destroy_sem_group(prime->sem_group_last_eating_time,
			prime->unique_names_last_eating_time, prime->n_philo);
	if (prime->unique_names_last_eating_time)
		free_strs(prime->unique_names_last_eating_time, prime->n_philo);
	if (prime->pids_philo)
		free(prime->pids_philo);
	if (prime->sem_forks && prime->sem_forks != SEM_FAILED)
		sem_close(prime->sem_forks);
	if (prime->sem_print && prime->sem_print != SEM_FAILED)
		sem_close(prime->sem_print);
}

static void	*monitor(void *arg)
{
	long int	curr_time;
	t_prime		*prime;

	prime = (t_prime *)arg;
	while (1)
	{
		sem_wait(prime->sem_group_last_eating_time[prime->philo_id]);
		curr_time = get_curr_time();
		if (curr_time - prime->last_eating_time > prime->time_to_die)
		{
			sem_post(prime->sem_group_last_eating_time[prime->philo_id]);
			sem_wait(prime->sem_print);
			printf("%ld %ld died\n",
				curr_time - prime->start_time, prime->philo_id);
			free_philo_proc_data(prime);
			exit(EXIT_FAILURE);
		}
		sem_post(prime->sem_group_last_eating_time[prime->philo_id]);
	}
	return (NULL);
}

static void	philo(t_prime *prime)
{
	pthread_t	thread_monitor;

	if (pthread_create(&thread_monitor, NULL, monitor, prime))
	{
		sem_wait(prime->sem_print);
		write(STDERR_FILENO, "\nInit error\n", 12);
		free_philo_proc_data(prime);
		exit(EXIT_FAILURE);
	}
	pthread_detach(thread_monitor);
	while (1)
	{
		philo_take_fork(prime);
		philo_take_fork(prime);
		philo_eat(prime);
		if (prime->n_eat == 0)
		{
			free_philo_proc_data(prime);
			exit(EXIT_SUCCESS);
		}
		philo_sleep(prime);
		philo_think(prime);
	}
}

void	destroy_philo_processes(t_prime *prime)
{
	ssize_t	i;

	if (!prime->pids_philo)
		return ;
	i = -1;
	while (++i < prime->n_created_philo)
		kill(prime->pids_philo[i], SIGKILL);
	prime->n_created_philo = 0;
	free(prime->pids_philo);
	prime->pids_philo = NULL;
}

int	create_philo_processes(t_prime *prime)
{
	ssize_t	i;

	prime->pids_philo = (pid_t *)malloc(sizeof(pid_t) * prime->n_philo);
	if (!prime->pids_philo)
		return (ERROR);
	prime->start_time = get_curr_time();
	i = -1;
	while (++i < prime->n_philo)
	{
		prime->n_created_philo = i;
		prime->philo_id = i;
		prime->pids_philo[i] = fork();
		if (prime->pids_philo[i] == -1)
			return (ERROR);
		else if (prime->pids_philo[i] == 0)
			philo(prime);
	}
	return (SUCCESS);
}
