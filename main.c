/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:55:46 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/08 14:27:58 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philosophers.h"

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

static void	join_threads(t_prime *prime)
{
	ssize_t	i;

	i = -1;
	while (++i < prime->philo_nb)
		pthread_join(prime->philos[i].thread_id, NULL);
	pthread_join(prime->monitor, NULL);
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
	init_prime(&prime, parsed_data.philo_nb);
	if (init_mutex(&prime.finish_mutex, &prime.finish_mutex_destroyed)
		|| init_mutexes(&prime.forks, prime.philo_nb)
		|| init_mutexes(&prime.last_eating_time_mutexes, prime.philo_nb)
		|| init_philo(&parsed_data, &prime)
		|| start_philo(&prime)
		|| start_monitor(&prime)
	)
	{
		printf("Init error\n");
		free_prime(&prime);
		return (0);
	}
	join_threads(&prime);
	free_prime(&prime);
	return (0);
}
