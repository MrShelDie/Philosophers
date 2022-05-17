#include "philo_bonus.h"

static void	philo_take_fork(t_prime *prime)
{
	sem_wait(prime->sem_forks);
	print_msg(prime, "has taken a fork\n");
}

static void	philo_eat(t_prime *prime)
{
	
}

void	philo_loop(t_prime *prime)
{
	while (prime->neat != UNDEF_EAT_NB && prime->time_to_eat > 0)
	{
		philo_take_fork(prime);
		philo_take_fork(prime);

	}
}
