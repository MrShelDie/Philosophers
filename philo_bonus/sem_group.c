/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_group.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:42:09 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/17 20:00:34 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

/**
 * @brief Generates an array of unique names
 * 
 * @param default_name - The common name by which unique names are generated
 * @param nname - Number of names to be generated
 * @return char** - On success, a pointer to an array of names
 * 		is returned, on error, NULL is returned.
 */
char	**generate_unique_names(const char *default_name, size_t nname)
{
	char	**unique_names;
	char	*unique_name;
	size_t	i;

	unique_names = (char **)malloc(sizeof(char *) * nname);
	if (!unique_names)
		return (NULL);
	i = -1;
	while (++i < nname)
	{
		unique_name = ft_itoa(i);
		if (!unique_name)
		{
			free_strs(unique_names, i);
			return (NULL);
		}
		unique_names[i] = ft_strjoin(default_name, unique_name);
		free(unique_name);
		if (!unique_names[i])
		{
			free_strs(unique_names, i);
			return (NULL);
		}
	}
	return (unique_names);
}

/**
 * @brief Closes and destroys a group of semaphores
 * 
 * @param sem_group - array of semaphores to be closed
 * @param unique_names - Array of unique names for each
 * 		semaphore from the semaphore group
 * @param nsem - number of semaphores in a group
 */
void	destroy_sem_group(
			sem_t **sem_group, char *const *unique_names, size_t nsem)
{
	size_t	i;

	i = -1;
	while (++i < nsem)
	{
		sem_close(sem_group[i]);
		sem_unlink(unique_names[i]);
	}
}

/**
 * @brief Creates and opens a group of semaphore objects
 * 
 * @param unique_names - Array of unique names for each
 * 		semaphore from the semaphore group
 * @param nsem - number of semaphores in a group
 * @param value - the values of each semaphore
 * @return sem_t** - if successful, a pointer to the semaphore
 * 		group is returned, in case of an error, NULL is returned.
 */
sem_t	**create_sem_group(char *const *unique_names, size_t nsem, int value)
{
	sem_t	**sem_group;
	size_t	i;

	sem_group = (sem_t **)malloc(sizeof(sem_t *) * nsem);
	if (!sem_group)
		return (NULL);
	i = -1;
	while (++i < nsem)
	{
		sem_group[i] = sem_open(unique_names[i], O_CREAT, 0666, value);
		if (sem_group[i] == SEM_FAILED)
		{
			destroy_sem_group(sem_group, unique_names, i);
			return (NULL);
		}
	}
	return (sem_group);
}
