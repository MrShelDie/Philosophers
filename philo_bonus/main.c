/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/17 19:39:27 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static int	parse(int argc, char *const *argv, t_prime *prime)
{
	bool	err;

	if (argc != ARGC_WITHOUT_EAT_NB && argc != ARGC_WITH_EAT_NB)
		return (ERROR);
	err = false;
	prime->n_philo = ft_atoi(argv[1], &err);
	prime->time_to_die = ft_atoi(argv[2], &err);
	prime->time_to_eat = ft_atoi(argv[3], &err);
	prime->time_to_sleep = ft_atoi(argv[4], &err);
	if (argc == ARGC_WITH_EAT_NB)
		prime->n_eat = ft_atoi(argv[5], &err);
	else
		prime->n_eat = UNDEF_EAT_NB;
	if (err || prime->n_philo <= 0 || prime->time_to_die <= 0
		|| prime->time_to_eat <= 0 || prime->time_to_sleep <= 0
		|| (argc == ARGC_WITH_EAT_NB && prime->n_eat <= 0))
		return (ERROR);
	return (SUCCESS);
}

static int	prime_init(t_prime *prime)
{
	memset(prime, 0, sizeof(t_prime));
	prime->unique_names_last_eating_time
		= generate_unique_names(SEM_GROUP_LAST_EATING_TIME, prime->n_philo);
	if (!prime->unique_names_last_eating_time)
		return (ERROR);
	prime->sem_group_last_eating_time = create_sem_group(
			prime->unique_names_last_eating_time, prime->n_philo, 1);
	if (!prime->sem_group_last_eating_time)
		return (ERROR);
	prime->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0666, prime->n_philo);
	if (prime->sem_forks == SEM_FAILED)
		return (ERROR);
	prime->sem_print = sem_open(SEM_PRINT, O_CREAT, 0666, 1);
	if (prime->sem_print == SEM_FAILED)
		return (ERROR);
	return (SUCCESS);
}

static void	prime_free(t_prime *prime)
{
	destroy_philo_processes(prime);
	if (prime->unique_names_last_eating_time
		&& prime->sem_group_last_eating_time
	)
		destroy_sem_group(prime->sem_group_last_eating_time,
			prime->unique_names_last_eating_time, prime->n_philo);
	if (prime->unique_names_last_eating_time)
		free_strs(prime->unique_names_last_eating_time, prime->n_philo);
	if (prime->sem_forks && prime->sem_forks != SEM_FAILED)
	{
		sem_close(prime->sem_forks);
		sem_unlink(SEM_FORKS);
	}
	if (prime->sem_print && prime->sem_print != SEM_FAILED)
	{
		sem_close(prime->sem_print);
		sem_unlink(SEM_PRINT);
	}
}

static void	wait_philos(t_prime *prime)
{
	int		exit_status;
	pid_t	ended_first;
	ssize_t	i;

	if (prime->n_created_philo == 0)
		return ;
	ended_first = waitpid(i, &exit_status, 0);
	if (exit_status == EXIT_FAILURE)
	{
		delay(prime->time_to_die);
		kill_except(prime->pids_philo, prime->n_created_philo, ended_first);
	}
	i = 0;
	while (++i < prime->n_created_philo)
		waitpid(-1, NULL, 0);
	prime->n_created_philo = 0;
	free(prime->pids_philo);
	prime->pids_philo = NULL;
}

int	main(int argc, char **argv)
{
	t_prime			prime;

	if (parse(argc, argv, &prime))
	{
		write(STDERR_FILENO, "\nInvalid argument\n", 18);
		return (0);
	}
	if (prime_init(&prime) || create_philo_processes(&prime))
	{
		prime_free(&prime);
		write(STDERR_FILENO, "\nInit error\n", 12);
		return (0);
	}
	wait_philos(&prime);
	prime_free(&prime);
	return (0);
}
