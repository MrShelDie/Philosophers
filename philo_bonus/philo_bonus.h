/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:20 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/17 15:41:06 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdbool.h>
# include <semaphore.h>

# define ERROR 1
# define SUCCESS 0

# define UNDEF_EAT_NB -1

# define ARGC_WITHOUT_EAT_NB 5
# define ARGC_WITH_EAT_NB 6

# define SEM_FORKS_NAME "/sem_forks"
# define SEM_PRINT_NAME "/sem_print"
# define SEM_LAST_EATING_TIME_NAME "/sem_last_eating_time"

# define EXIT_SUCCESS	0
# define EXIT_INIT_ERR	1

typedef struct timeval	t_timeval;

typedef struct s_prime
{
	pid_t		*pids_philo;

	sem_t		*sem_forks;
	sem_t		*sem_print;
	sem_t		**sem_group_last_eating_time;
	char		**unique_names_last_eating_time;

	long int	start_time;
	int			neat;

	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			philo_id;

	int			nphilo;
	int			created_philo_nb;
}				t_prime;

int			create_philo_processes(t_prime *prime);
void		destroy_philo_processes(t_prime *prime);

sem_t		**create_sem_group(
				const char **unique_names, size_t nsem, int value);
void		destroy_sem_group(
				sem_t **sem_group, const char **unique_names, size_t nsem);
char		**generate_unique_names(const char *default_name, size_t nname);

void		delay(unsigned int ms);
void		free_strs(char **strs, size_t nstr);
void		print_msg(t_prime *prime, const char *msg);
long int	get_curr_time(void);

int			ft_atoi(const char *str, bool *err);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);

#endif
