/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:55:46 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/07 20:46:56 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "philosophers.h"

static int	parse(int argc, char *const *argv, t_parsed_data *parsed_data)
{
	bool	err;

	if (argc != ARGC_WITHOUT_EAT_NB && argc != ARGC_WITH_EAT_NB)
		return (ERROR);
	err = false;
	parsed_data->philo_nb = ft_atoui(argv[1], &err);
	parsed_data->time_to_die = ft_atoui(argv[2], &err);
	parsed_data->time_to_eat = ft_atoui(argv[3], &err);
	parsed_data->time_to_sleep = ft_atoui(argv[4], &err);
	if (argc == ARGC_WITH_EAT_NB)
		parsed_data->eat_nb = (long int)ft_atoui(argv[5], &err);
	else
		parsed_data->eat_nb = UNDEF_EAT_NB;
	if (err)
		return (ERROR);
	return (SUCCESS);
}

// static int	init_fork(t_prime *prime)
// {
// 	ssize_t	i;
// 	bool	err;

// 	prime->forks = (t_mutex *)malloc(sizeof(t_mutex) * prime->philo_nb);
// 	if (!prime->forks)
// 		return (ERROR);
// 	err = false;
// 	i = -1;
// 	while (++i < prime->philo_nb && !err)
// 	{
// 		if (pthread_mutex_init(&prime->forks[i], NULL))
// 			err = true;
// 	}
// 	if (err)
// 	{
// 		while (--i > -1)
// 			pthread_mutex_destroy(&prime->forks[i]);
// 		free(prime->forks);
// 		prime->forks = NULL;
// 		return (ERROR);
// 	}
// 	return (SUCCESS);
// }

static int	init_mutexes(t_mutex **mutexes, unsigned int mutex_nb)
{
	ssize_t	i;
	bool	err;

	*mutexes = (t_mutex *)malloc(sizeof(t_mutex) * mutex_nb);
	if (!*mutexes)
		return (ERROR);
	err = false;
	i = -1;
	while (++i < mutex_nb && !err)
	{
		if (pthread_mutex_init(&(*mutexes)[i], NULL))
			err = true;
	}
	if (err)
	{
		while (--i > -1)
			pthread_mutex_destroy(&(*mutexes)[i]);
		free(*mutexes);
		*mutexes = NULL;
		return (ERROR);
	}
	return (SUCCESS);
}

static int	init_philo(t_parsed_data const *parsed_data, t_prime *prime)
{
	long int	i;
	t_philo		*philo;

	prime->philos = (t_philo *)malloc(sizeof(t_philo) * prime->philo_nb);
	if (!prime->philos)
		return (ERROR);
	i = -1;
	while (++i < prime->philo_nb)
	{
		philo = &prime->philos[i];
		philo->finish = &prime->finish;
		philo->finish_mutex = &prime->finish_mutex;
		philo->print_mutex = &prime->print_mutex;
		philo->forks[i % 2] = &prime->forks[(i + 1) % prime->philo_nb];
		philo->forks[(i + 1) % 2] = &prime->forks[i];
		philo->last_eating_time = -1;
		philo->time_to_die = parsed_data->time_to_die;
		philo->time_to_eat = parsed_data->time_to_eat;
		philo->time_to_sleep = parsed_data->time_to_sleep;
		philo->philo_id = (unsigned int)i;
		philo->remain_eat_nb = parsed_data->eat_nb;
	}
	return (SUCCESS);
}

static void	free_mutexes(t_mutex **mutexes, unsigned int mutex_nb)
{
	ssize_t	i;

	if (*mutexes)
	{
		i = -1;
		while (++i < mutex_nb)
			pthread_mutex_destroy(&(*mutexes)[i]);
		free(*mutexes);
		*mutexes = NULL;
	}
}

static int	init_mutex(t_mutex *mutex, bool *mutex_destroyed)
{
	if (pthread_mutex_init(mutex, NULL))
	{
		*mutex_destroyed = true;
		return (ERROR);
	}
	else
	{
		*mutex_destroyed = false;
		return (SUCCESS);
	}
}

static void	free_prime(t_prime *prime)
{
	free_mutexes(&prime->forks, prime->philo_nb);
	free_mutexes(&prime->last_eating_time_mutexes, prime->philo_nb);
	if (!prime->print_mutex_destroyed)
		pthread_mutex_destroy(&prime->print_mutex);
	if (!prime->finish_mutex_destroyed)
		pthread_mutex_destroy(&prime->finish_mutex);
	if (prime->philos)
	{
		free(prime->philos);
		prime->philos = NULL;
	}
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
	memset(&prime, 0, sizeof(prime));
	prime.finish = false;
	prime.philo_nb = parsed_data.philo_nb;
	if (init_mutex(&prime.print_mutex, &prime.print_mutex_destroyed)
		|| init_mutex(&prime.finish_mutex, &prime.finish_mutex_destroyed)
		|| init_mutexes(&prime.forks, prime.philo_nb)
		|| init_mutexes(&prime.last_eating_time_mutexes, prime.philo_nb)
		|| init_philo(&parsed_data, &prime)
	)
	{
		printf("Init error\n");
		free_prime(&prime);
		return (0);
	}
	free_prime(&prime);
	return (0);
}
