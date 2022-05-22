/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:20 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/22 13:28:17 by gannemar         ###   ########.fr       */
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

# define SEM_FORKS "/forks"
# define SEM_PRINT "/print"
# define SEM_EATING_PHILO "/eating_philo"
# define SEM_GROUP_N_EAT "/n_eat_"
# define SEM_GROUP_KILL "/kill_philo_"
# define SEM_GROUP_LET "/last_eating_time_"

typedef struct timeval	t_timeval;

typedef struct s_prime
{
	pid_t		*pids_philo;

	sem_t		*sem_forks;
	sem_t		*sem_print;
	sem_t		**sem_group_let;
	sem_t		**sem_group_kill;
	sem_t		*sem_eating_philo;

	char		**unames_kill;
	char		**unames_let;

	long int	start_time;
	long int	last_eating_time;
	int			n_eat;

	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			philo_id;

	int			n_philo;
	int			n_created_philo;
}				t_prime;

int			create_philos(t_prime *prime);
void		wait_philos(t_prime *prime);

sem_t		**create_sem_group(
				char *const *unique_names, size_t nsem, int value);
void		destroy_sem_group(sem_t **sem_group, size_t nsem);
char		**gen_unames(const char *default_name, size_t nname);

void		delay(unsigned int ms);
void		free_strs(char **strs, size_t nstr);
void		print_msg(t_prime *prime, const char *msg);
void		kill_all(pid_t *pids, size_t n_pids, sem_t **sem_group_kill_philo);
void		wait_remain(size_t n_ended_proc, size_t n_proc_to_wait);
long int	get_curr_time(void);

int			ft_atoi(const char *str, bool *err);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);

void		philo_take_fork(t_prime *prime);
void		philo_eat(t_prime *prime);
void		philo_think(t_prime *prime);
void		philo_sleep(t_prime *prime);

#endif
