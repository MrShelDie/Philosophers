/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/14 13:36:14 by gannemar         ###   ########.fr       */
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
	prime->philo_nb = atoui(argv[1], &err);
	prime->time_to_die = atoui(argv[2], &err);
	prime->time_to_eat = atoui(argv[3], &err);
	prime->time_to_sleep = atoui(argv[4], &err);
	if (argc == ARGC_WITH_EAT_NB)
		prime->eat_nb = (long int)atoui(argv[5], &err);
	else
		prime->eat_nb = UNDEF_EAT_NB;
	if (err)
		return (ERROR);
	return (SUCCESS);
}

static int	prime_init(t_prime *prime)
{
	memset(prime, 0, sizeof(t_prime));
	prime->sem_forks = sem_open(SEM_FORKS_NAME, O_CREAT, 0666, prime->philo_nb);
	if (prime->sem_forks == SEM_FAILED)
		return (ERROR);
	prime->sem_print = sem_open(SEM_PRINT_NAME, O_CREAT, 0666, 1);
	if (prime->sem_print == SEM_FAILED)
		return (ERROR);
	return (SUCCESS);
}

static void	prime_free(t_prime *prime)
{
	philos_destroy(prime);
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
	int		status;
	ssize_t	i;

	status = EXIT_SUCCESS;
	i = -1;
	while (++i < prime->created_philo_nb)
	{
		wait(&status);
		if (status == EXIT_INIT_ERR)
		{
			philos_destroy(prime);
			write(STDERR_FILENO, "Init error\n", 11);
			return ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_prime			prime;

	if (parse(argc, argv, &prime))
	{
		write(STDERR_FILENO, "Invalid argument\n", 17);
		return (0);
	}
	if (prime_init(&prime) || philos_create(&prime))
	{
		prime_free(&prime);
		write(STDERR_FILENO, "Init error\n", 11);
		return (0);
	}
	wait_philos(&prime);
	prime_free(&prime);
	return (0);
}
