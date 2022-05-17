/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/17 15:42:21 by gannemar         ###   ########.fr       */
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
	prime->nphilo = ft_atoi(argv[1], &err);
	prime->time_to_die = ft_atoi(argv[2], &err);
	prime->time_to_eat = ft_atoi(argv[3], &err);
	prime->time_to_sleep = ft_atoi(argv[4], &err);
	if (argc == ARGC_WITH_EAT_NB)
		prime->neat = ft_atoi(argv[5], &err);
	else
		prime->neat = UNDEF_EAT_NB;
	if (err || prime->nphilo <= 0 || prime->time_to_die <= 0
		|| prime->time_to_eat <= 0 || prime->time_to_sleep <= 0
		|| (argc == ARGC_WITH_EAT_NB && prime->neat <= 0))
		return (ERROR);
	return (SUCCESS);
}

static int	prime_init(t_prime *prime)
{
	memset(prime, 0, sizeof(t_prime));
	prime->unique_names_last_eating_time
		= generate_unique_names(SEM_LAST_EATING_TIME_NAME, prime->nphilo);
	if (!prime->unique_names_last_eating_time)
		return (ERROR);
	prime->sem_group_last_eating_time = create_sem_group(
			prime->unique_names_last_eating_time, prime->nphilo, 1);
	if (!prime->sem_group_last_eating_time)
		return (ERROR);
	prime->sem_forks = sem_open(SEM_FORKS_NAME, O_CREAT, 0666, prime->nphilo);
	if (prime->sem_forks == SEM_FAILED)
		return (ERROR);
	prime->sem_print = sem_open(SEM_PRINT_NAME, O_CREAT, 0666, 1);
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
			prime->unique_names_last_eating_time, prime->nphilo);
	if (prime->unique_names_last_eating_time)
		free_strs(prime->unique_names_last_eating_time, prime->nphilo);
	if (prime->sem_forks && prime->sem_forks != SEM_FAILED)
	{
		sem_close(prime->sem_forks);
		sem_unlink(SEM_FORKS_NAME);
	}
	if (prime->sem_print && prime->sem_print != SEM_FAILED)
	{
		sem_close(prime->sem_print);
		sem_unlink(SEM_PRINT_NAME);
	}
}

static void	wait_philos(t_prime *prime)
{
	ssize_t	i;

	i = -1;
	while (++i < prime->created_philo_nb)
		wait(NULL);
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
