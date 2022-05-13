/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:08:29 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/13 20:50:31 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <stdlib.h>

static void	philo(t_prime *prime)
{
	// TODO
}

void	philos_destroy(t_prime *prime)
{
	ssize_t	i;

	i = -1;
	while (++i < prime->created_philo_nb)
		kill(prime->pid_philos[i], SIGKILL);
	free(prime->pid_philos);
	prime->pid_philos = NULL;
}

int	philo_create(t_prime *prime)
{
	ssize_t	i;

	prime->pid_philos = (pid_t *)malloc(sizeof(pid_t) * prime->philo_nb);
	if (!prime->pid_philos)
		return (ERROR);
	i = -1;
	while (++i < prime->philo_nb)
	{
		prime->pid_philos[i] = fork();
		if (prime->pid_philos[i] == -1)
		{
			prime->created_philo_nb = i;
			philos_destroy(prime);
			return (ERROR);
		}
		else if (prime->pid_philos[i] == 0)
			philo(prime);
	}
	return (SUCCESS);
}
