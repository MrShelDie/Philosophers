/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:55:46 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/07 13:05:39 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "philosophers.h"

static int	parse(int argc, char *const *argv, t_parsed_data *parsed_data)
{
	bool	err;

	if (argc != 5 && argc != 6)
		return (ERROR);
	err = false;
	parsed_data->philo_nb = ft_atoui(argv[1], &err);
	parsed_data->time_to_die = ft_atoui(argv[2], &err);
	parsed_data->time_to_eat = ft_atoui(argv[3], &err);
	parsed_data->time_to_sleep = ft_atoui(argv[4], &err);
	if (argc == 6)
	{
		parsed_data->eat_nb = ft_atoui(argv[5], &err);
		parsed_data->is_eat_nb_defined = true;
	}
	else
		parsed_data->is_eat_nb_defined = false;
	if (err)
		return (ERROR);
	return (SUCCESS);
}

static int	fork_init(t_prime *prime)
{
	ssize_t	i;
	bool	err;

	prime->forks = (t_mutex *)malloc(sizeof(t_mutex) * prime->philo_nb);
	if (!prime->forks)
		return (ERROR);
	err = false;
	i = -1;
	while (++i < prime->philo_nb && !err)
	{
		if (pthread_mutex_init(&prime->forks[i], NULL))
			err = true;
	}
	if (err)
	{
		while (--i > -1)
			pthread_mutex_destroy(&prime->forks[i]);
		prime->forks_destroyed = true;
		return (ERROR);
	}
	prime->forks_destroyed = false;
	return (SUCCESS);
}

static void	free_prime(t_prime *prime)
{
	ssize_t	i;

	if (!prime->forks_destroyed)
	{
		i = -1;
		while (++i < prime->philo_nb)
			pthread_mutex_destroy(&prime->forks[i]);
		prime->forks_destroyed = true;
	}
	free(prime->forks);
}

int	main(int argc, char **argv)
{
	t_prime			prime;
	t_parsed_data	parsed_data;

	if (parse(argc, argv, &parsed_data))
	{
		printf("Invalid argument\n");
		return (0);
	}
	prime.philo_nb = parsed_data.philo_nb;
	if (fork_init(&prime))
	{
		printf("Fork init error\n");
		return (0);
	}
	free_prime(&prime);
	return (0);
}
