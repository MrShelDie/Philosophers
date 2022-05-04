/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:09:28 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/04 23:17:08 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>

# define ERROR 0
# define SUCCESS 1

typedef struct s_parser_data
{
	unsigned int	philo_nb;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	eat_nb;
	bool			is_eat_nb_defined;
}	t_parsed_data;

unsigned int	ft_atoui(const char *str, bool *err);

#endif
