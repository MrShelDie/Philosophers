/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 01:57:41 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/11 20:24:13 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *arg)
{
	print_msg(arg, "is thinking\n");
}

void	philo_take_fork(t_philo *arg, unsigned int fork_num)
{
	pthread_mutex_lock(arg->forks[fork_num]);
	print_msg(arg, "has taken a fork\n");
	if (arg->forks[0] == arg->forks[1])
	{
		delay(arg->time_to_die + 1);
		pthread_mutex_unlock(arg->forks[fork_num]);
	}
}

void	philo_eat(t_philo *arg)
{
	// pthread_mutex_lock(arg->last_eating_time_mutex);
	// arg->last_eating_time = get_curr_time();
	// pthread_mutex_unlock(arg->last_eating_time_mutex);
	print_msg(arg, "is eating\n");
	delay(arg->time_to_eat);
	pthread_mutex_lock(arg->last_eating_time_mutex);
	arg->last_eating_time = get_curr_time();
	pthread_mutex_unlock(arg->last_eating_time_mutex);
	pthread_mutex_lock(arg->eat_nb_mutex);
	if (arg->eat_nb > 0)
		arg->eat_nb--;
	pthread_mutex_unlock(arg->eat_nb_mutex);
}

void	philo_sleep(t_philo *arg)
{
	print_msg(arg, "is sleeping\n");
	pthread_mutex_unlock(arg->forks[1]);
	pthread_mutex_unlock(arg->forks[0]);
	delay(arg->time_to_sleep);
}
