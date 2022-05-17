/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:08:29 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/17 15:32:27 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void	free_philo_proc_data(t_prime *prime)
{
	if (prime->pids_philo)
		free(prime->pids_philo);
	if (prime->sem_forks && prime->sem_forks != SEM_FAILED)
		sem_close(prime->sem_forks);
	if (prime->sem_print && prime->sem_print != SEM_FAILED)
		sem_close(prime->sem_print);
}

static void	*monitor(void *arg)
{
	// TODO
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
		exit(EXIT_INIT_ERR);
	}
	pthread_detach(thread_monitor);
	// TODO
}

void	destroy_philo_processes(t_prime *prime)
{
	ssize_t	i;

	if (!prime->pids_philo)
		return ;
	i = -1;
	while (++i < prime->created_philo_nb)
		kill(prime->pids_philo[i], SIGKILL);
	prime->created_philo_nb = 0;
	free(prime->pids_philo);
	prime->pids_philo = NULL;
}

int	create_philo_processes(t_prime *prime)
{
	ssize_t	i;

	prime->pids_philo = (pid_t *)malloc(sizeof(pid_t) * prime->nphilo);
	if (!prime->pids_philo)
		return (ERROR);
	prime->start_time = get_curr_time();
	i = -1;
	while (++i < prime->nphilo)
	{
		prime->created_philo_nb = i;
		prime->philo_id = i;
		prime->pids_philo[i] = fork();
		if (prime->pids_philo[i] == -1)
			return (ERROR);
		else if (prime->pids_philo[i] == 0)
			philo(prime);
	}
	return (SUCCESS);
}
