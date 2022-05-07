/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:55:46 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/07 12:09:40 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

int	main(int argc, char **argv)
{
	t_parsed_data	parsed_data;

	if (!parse(argc, argv, &parsed_data))
	{
		printf("Invalid argument\n");
		return (0);
	}
	return (0);
}
