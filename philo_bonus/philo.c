/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:08:29 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/14 13:47:35 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void	free_philo_data(t_prime *prime)
{
	if (prime->pid_philos)
		free(prime->pid_philos);
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

	prime->sem_forks = sem_open(SEM_FORKS_NAME, 0);
	prime->sem_print = sem_open(SEM_PRINT_NAME, 0);
	if (prime->sem_forks == SEM_FAILED || prime->sem_print == SEM_FAILED
		|| pthread_create(&thread_monitor, NULL, monitor, prime))
	{
		free_philo_data(prime);
		exit(EXIT_INIT_ERR);
	}
	pthread_detach(thread_monitor);
	// TODO
}

void	philos_destroy(t_prime *prime)
{
	ssize_t	i;

	if (!prime->pid_philos)
		return ;
	i = -1;
	while (++i < prime->created_philo_nb)
		kill(prime->pid_philos[i], SIGKILL);
	prime->created_philo_nb = 0;
	free(prime->pid_philos);
	prime->pid_philos = NULL;
}

int	philos_create(t_prime *prime)
{
	ssize_t	i;

	prime->pid_philos = (pid_t *)malloc(sizeof(pid_t) * prime->philo_nb);
	if (!prime->pid_philos)
		return (ERROR);
	prime->start_time = get_curr_time();
	i = -1;
	while (++i < prime->philo_nb)
	{
		prime->created_philo_nb = i;
		prime->philo_id = i;
		prime->pid_philos[i] = fork();
		if (prime->pid_philos[i] == -1)
			return (ERROR);
		else if (prime->pid_philos[i] == 0)
			philo(prime);
	}
	return (SUCCESS);
}
