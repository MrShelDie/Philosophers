/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 01:57:41 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/08 14:31:30 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_think(t_philo *arg)
{
	if (arg->remain_eat_nb != UNDEF_EAT_NB && arg->remain_eat_nb <= 0)
		return (EXIT_THREAD);
	if (print_msg(arg, "is thinking\n"))
		return (EXIT_THREAD);
	return (CONTINUE_THREAD);
}

int	philo_take_fork(t_philo *arg, t_mutex *fork)
{
	pthread_mutex_lock(fork);
	if (print_msg(arg, "has taken a fork\n"))
	{
		pthread_mutex_unlock(fork);
		return (EXIT_THREAD);
	}
	return (CONTINUE_THREAD);
}

int	philo_put_fork(t_mutex *fork)
{
	pthread_mutex_unlock(fork);
	return (CONTINUE_THREAD);
}

int	philo_eat(t_philo *arg)
{
	pthread_mutex_lock(arg->last_eating_time_mutex);
	arg->last_eating_time = get_curr_time();
	pthread_mutex_unlock(arg->last_eating_time_mutex);
	if (print_msg(arg, "is eating\n"))
	{
		pthread_mutex_unlock(arg->forks[0]);
		pthread_mutex_unlock(arg->forks[1]);
		return (EXIT_THREAD);
	}
	delay(arg->time_to_eat);
	return (CONTINUE_THREAD);
}

int	philo_sleep(t_philo *arg)
{
	if (print_msg(arg, "is sleeping\n"))
		return (EXIT_THREAD);
	delay(arg->time_to_sleep);
	return (CONTINUE_THREAD);
}
