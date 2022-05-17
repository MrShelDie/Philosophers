/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:27:46 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/18 02:00:05 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_take_fork(t_prime *prime)
{
	sem_wait(prime->sem_forks);
	print_msg(prime, "has taken a fork\n");
}

void	philo_eat(t_prime *prime)
{
	print_msg(prime, "is eating\n");
	delay(prime->time_to_eat);
	sem_wait(prime->sem_group_last_eating_time[prime->philo_id]);
	prime->last_eating_time = get_curr_time();
	sem_post(prime->sem_group_last_eating_time[prime->philo_id]);
	if (prime->n_eat > 0)
		prime->n_eat--;
}

void	philo_think(t_prime *prime)
{
	print_msg(prime, "is thinking\n");
}

void	philo_sleep(t_prime *prime)
{
	print_msg(prime, "is sleeping\n");
	sem_post(prime->sem_forks);
	sem_post(prime->sem_forks);
	delay(prime->time_to_sleep);
}
