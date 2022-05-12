/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:20 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/12 15:14:22 by gannemar         ###   ########.fr       */
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

# define SEM_FORKS_NAME "/forks"
# define SEM_STDOUT_NAME "/stdout"

typedef struct s_prime
{
	pid_t			*pid_philos;
	sem_t			*sem_forks;
	sem_t			*sem_stdout;
	unsigned int	philo_nb;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	created_philo_nb;
	long int		eat_nb;
}					t_prime;

unsigned int	atoui(const char *str, bool *err);

int				philo_create(t_prime *prime);
void			philos_destroy(t_prime *prime);

#endif
