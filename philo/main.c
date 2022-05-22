/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:55:46 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/22 14:23:33 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <sys/types.h>

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
	if (err || parsed_data->philo_nb <= 0 || parsed_data->time_to_die <= 0
		|| parsed_data->time_to_eat <= 0 || parsed_data->time_to_sleep <= 0
		|| (argc == ARGC_WITH_EAT_NB && parsed_data->eat_nb <= 0))
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
		write(2, "Invalid argument\n", 17);
		return (0);
	}
	if (init_prime(&parsed_data, &prime))
	{
		join_threads(&prime);
		free_prime(&prime);
		write(2, "Init error\n", 11);
		return (0);
	}
	join_threads(&prime);
	free_prime(&prime);
	return (0);
}
