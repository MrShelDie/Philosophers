/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:55:46 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/07 16:05:35 by gannemar         ###   ########.fr       */
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
		parsed_data->eat_nb = (long int)ft_atoui(argv[5], &err);
	else
		parsed_data->eat_nb = UNDEF_EAT_NB;
	if (err)
		return (ERROR);
	return (SUCCESS);
}

static int	init_fork(t_prime *prime)
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
	return (SUCCESS);
}

static int	init_philo(t_parsed_data const *parsed_data, t_prime *prime)
{
	ssize_t	i;
	t_philo	*philo;

	prime->philos = (t_philo *)malloc(sizeof(t_philo) * prime->philo_nb);
	if (!prime->philos)
		return (ERROR);
	i = -1;
	while (++i < prime->philo_nb)
	{
		philo = &prime->philos[i];
		philo->finish = &prime->finish;
		philo->forks[i % 2] = &prime->forks[(i + 1) % prime->philo_nb];
		philo->forks[(i + 1) % 2] = &prime->forks[i];
		philo->last_eating_sec = -1;
		philo->last_eating_usec = -1;
		philo->time_to_die = parsed_data->time_to_die;
		philo->time_to_eat = parsed_data->time_to_eat;
		philo->time_to_sleep = parsed_data->time_to_sleep;
		philo->remain_eat_nb = parsed_data->eat_nb;
	}
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
	free(prime->philos);
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
	prime.finish = false;
	prime.forks_destroyed = false;
	prime.philo_nb = parsed_data.philo_nb;
	if (init_fork(&prime) || init_philo(&parsed_data, &prime))
	{
		printf("Init error\n");
		return (0);
	}
	free_prime(&prime);
	return (0);
}
