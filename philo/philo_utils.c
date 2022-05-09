/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 01:57:41 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/09 15:51:30 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_think(t_philo *arg)
{
	pthread_mutex_lock(arg->finish_mutex);
	if (print_msg(arg, "is thinking\n"))
	{
		pthread_mutex_unlock(arg->finish_mutex);
		return (EXIT_THREAD);
	}
	pthread_mutex_unlock(arg->finish_mutex);
	return (CONTINUE_THREAD);
}

int	philo_take_fork(t_philo *arg, unsigned int fork_num)
{
	pthread_mutex_lock(arg->forks[fork_num]);
	pthread_mutex_lock(arg->finish_mutex);
	if (print_msg(arg, "has taken a fork\n"))
	{
		pthread_mutex_unlock(arg->finish_mutex);
		pthread_mutex_unlock(arg->forks[fork_num]);
		if (fork_num == 1)
			pthread_mutex_unlock(arg->forks[fork_num - 1]);
		return (EXIT_THREAD);
	}
	pthread_mutex_unlock(arg->finish_mutex);
	if (arg->forks[0] == arg->forks[1])
	{
		delay(arg->time_to_die);
		pthread_mutex_unlock(arg->forks[fork_num]);
		if (fork_num == 1)
			pthread_mutex_unlock(arg->forks[fork_num - 1]);
		return (EXIT_THREAD);
	}
	return (CONTINUE_THREAD);
}

int	philo_eat(t_philo *arg)
{
	if (arg->eat_nb != UNDEF_EAT_NB && arg->eat_nb <= 0)
	{
		pthread_mutex_unlock(arg->forks[1]);
		pthread_mutex_unlock(arg->forks[0]);
		return (EXIT_THREAD);
	}
	pthread_mutex_lock(arg->finish_mutex);
	pthread_mutex_lock(arg->last_eating_time_mutex);
	arg->last_eating_time = get_curr_time();
	pthread_mutex_unlock(arg->last_eating_time_mutex);
	if (print_msg(arg, "is eating\n"))
	{
		pthread_mutex_unlock(arg->finish_mutex);
		pthread_mutex_unlock(arg->forks[1]);
		pthread_mutex_unlock(arg->forks[0]);
		return (EXIT_THREAD);
	}
	pthread_mutex_unlock(arg->finish_mutex);
	delay(arg->time_to_eat);
	pthread_mutex_lock(arg->eat_nb_mutex);
	if (arg->eat_nb > 0)
		arg->eat_nb--;
	if (arg->eat_nb == 0)
	{
		pthread_mutex_unlock(arg->eat_nb_mutex);
		pthread_mutex_unlock(arg->forks[1]);
		pthread_mutex_unlock(arg->forks[0]);
		return (EXIT_THREAD);
	}
	pthread_mutex_unlock(arg->eat_nb_mutex);
	return (CONTINUE_THREAD);
}

int	philo_sleep(t_philo *arg)
{
	pthread_mutex_lock(arg->finish_mutex);
	if (print_msg(arg, "is sleeping\n"))
	{
		pthread_mutex_unlock(arg->finish_mutex);
		pthread_mutex_unlock(arg->forks[1]);
		pthread_mutex_unlock(arg->forks[0]);
		return (EXIT_THREAD);
	}
	pthread_mutex_unlock(arg->finish_mutex);
	pthread_mutex_unlock(arg->forks[1]);
	pthread_mutex_unlock(arg->forks[0]);
	delay(arg->time_to_sleep);
	return (CONTINUE_THREAD);
}
