/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/22 13:28:03 by gannemar         ###   ########.fr       */
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

static int	init_sem_groups(t_prime *prime)
{
	prime->unames_let = gen_unames(SEM_GROUP_LET, prime->n_philo);
	if (!prime->unames_let)
		return (ERROR);
	prime->sem_group_let
		= create_sem_group(prime->unames_let, prime->n_philo, 1);
	if (!prime->sem_group_let)
		return (ERROR);
	prime->unames_kill = gen_unames(SEM_GROUP_KILL, prime->n_philo);
	if (!prime->unames_kill)
		return (ERROR);
	prime->sem_group_kill
		= create_sem_group(prime->unames_kill, prime->n_philo, 1);
	if (!prime->sem_group_kill)
		return (ERROR);
	return (SUCCESS);
}

static int	prime_init(t_prime *prime)
{
	if (init_sem_groups(prime))
		return (ERROR);
	prime->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0666, prime->n_philo);
	if (prime->sem_forks == SEM_FAILED)
		return (ERROR);
	sem_unlink(SEM_FORKS);
	prime->sem_print = sem_open(SEM_PRINT, O_CREAT, 0666, 1);
	if (prime->sem_print == SEM_FAILED)
		return (ERROR);
	sem_unlink(SEM_PRINT);
	prime->sem_eating_philo
		= sem_open(SEM_EATING_PHILO, O_CREAT, 0666, prime->n_philo - 1);
	if (prime->sem_eating_philo == SEM_FAILED)
		return (ERROR);
	sem_unlink(SEM_EATING_PHILO);
	return (SUCCESS);
}

static void	prime_free(t_prime *prime)
{
	if (prime->unames_let
		&& prime->sem_group_let)
	{
		destroy_sem_group(prime->sem_group_let, prime->n_philo);
		free(prime->sem_group_let);
	}
	if (prime->unames_let)
		free_strs(prime->unames_let, prime->n_philo);
	if (prime->unames_kill
		&& prime->sem_group_kill)
	{
		destroy_sem_group(prime->sem_group_kill, prime->n_philo);
		free(prime->sem_group_kill);
	}
	if (prime->unames_kill)
		free_strs(prime->unames_kill, prime->n_philo);
	if (prime->sem_forks && prime->sem_forks != SEM_FAILED)
		sem_close(prime->sem_forks);
	if (prime->sem_print && prime->sem_print != SEM_FAILED)
		sem_close(prime->sem_print);
	if (prime->pids_philo)
		free(prime->pids_philo);
}

int	main(int argc, char **argv)
{
	t_prime			prime;

	memset(&prime, 0, sizeof(t_prime));
	if (parse(argc, argv, &prime))
	{
		write(STDERR_FILENO, "Invalid argument\n", 17);
		return (0);
	}
	if (prime_init(&prime) || create_philos(&prime))
	{
		wait_philos(&prime);
		prime_free(&prime);
		write(STDERR_FILENO, "Init error\n", 11);
		return (0);
	}
	wait_philos(&prime);
	prime_free(&prime);
	return (0);
}
