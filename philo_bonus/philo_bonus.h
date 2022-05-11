/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:20 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/11 21:00:49 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdbool.h>
# include <semaphore.h>

# define ERROR 1
# define SUCCESS 0

# define UNDEF_EAT_NB -1

# define ARGC_WITHOUT_EAT_NB 5
# define ARGC_WITH_EAT_NB 6

# define SEM_NAME "/forks"

typedef struct s_parser_data
{
	unsigned int	philo_nb;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long int		eat_nb;
}					t_parsed_data;

unsigned int	atoui(const char *str, bool *err);

#endif
