/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:29:10 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/22 13:35:30 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stddef.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void	free_strs(char **strs, size_t nstr)
{
	size_t	i;

	i = -1;
	while (++i < nstr)
		free(strs[i]);
	free(strs);
}

void	wait_remain(size_t n_ended_proc, size_t n_total_proc)
{
	size_t	i;

	i = n_ended_proc;
	while (i < n_total_proc)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

void	kill_all(pid_t *pids, size_t n_pids, sem_t **sem_group_kill_philo)
{
	size_t	i;

	i = -1;
	while (++i < n_pids)
	{
		sem_wait(sem_group_kill_philo[i]);
		kill(pids[i], SIGKILL);
		sem_post(sem_group_kill_philo[i]);
	}
}
