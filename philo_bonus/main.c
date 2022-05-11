/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/11 21:09:35 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

static int	parse(int argc, char *const *argv, t_parsed_data *parsed_data)
{
	bool	err;

	if (argc != ARGC_WITHOUT_EAT_NB && argc != ARGC_WITH_EAT_NB)
		return (ERROR);
	err = false;
	parsed_data->philo_nb = atoui(argv[1], &err);
	parsed_data->time_to_die = atoui(argv[2], &err);
	parsed_data->time_to_eat = atoui(argv[3], &err);
	parsed_data->time_to_sleep = atoui(argv[4], &err);
	if (argc == ARGC_WITH_EAT_NB)
		parsed_data->eat_nb = (long int)atoui(argv[5], &err);
	else
		parsed_data->eat_nb = UNDEF_EAT_NB;
	if (err)
		return (ERROR);
	return (SUCCESS);
}

static void	philos_destroy(pid_t *philos, unsigned int philo_nb)
{
	ssize_t	i;

	i = -1;
	while (++i < philo_nb)
		kill(philos[i], SIGKILL);
	free(philos);
	philos = NULL;
}

static int	philo_create(pid_t *philos, unsigned int philo_nb)
{
	ssize_t	i;

	philos = (pid_t *)malloc(sizeof(pid_t) * philo_nb);
	if (!philos)
		return (ERROR);
	i = -1;
	while (++i < philo_nb)
	{
		philos[i] = fork();
		if (philos[i] == -1)
		{
			// TODO
		}
		else if (philos[i] == 0)
		{
			// TODO
		}
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_parsed_data	parsed_data;
	pid_t			*philos;
	sem_t			*forks;

	if (parse(argc, argv, &parsed_data))
	{
		printf("Invalid argument\n");
		return (0);
	}
	forks = sem_open(SEM_NAME, O_CREAT, 0666, parsed_data.philo_nb);
	if (forks == SEM_FAILED)
	{
		printf("Can't create semaphore\n");
		return (0);
	}
	return (0);
}
