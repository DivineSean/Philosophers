/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:19:19 by markik            #+#    #+#             */
/*   Updated: 2023/07/22 02:02:02 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_philo *list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_destroy(&list->fork);
		list = list->next;
		i++;
	}
}

pthread_t	*my_threads(t_philo *list, long long len)
{
	int			i;
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * len);
	i = 0;
	while (i < len)
	{
		if (pthread_create(&thread[i], NULL, routine, list) == -1)
		{
			printf("fail to creat threads!!\n");
			break ;
		}
		if (pthread_detach(thread[i]) == -1)
		{
			printf("fail to detach threads!!\n");
			break ;
		}
		list = list->next;
		i++;
	}
	return (thread);
}

int	*filling_tab(long long len)
{
	long long	i;
	int			*tab;

	i = 0;
	tab = malloc(sizeof(int) * len);
	while (i < len)
		tab[i++] = -1;
	return (tab);
}

void	check_death(t_philo *list, int *id, int ac, long long len)
{
	int	j;

	j = 0;
	while (list)
	{
		pthread_mutex_lock(list->death);
		pthread_mutex_lock(list->num_eat);
		if (list->dead)
			break ;
		else if (ac > 5 && list->number_eat == 0 \
				&& id[list->id - 1] != list->id)
		{
			id[list->id - 1] = list->id;
			j++;
			if (j == len)
			{
				free(id);
				break ;
			}
		}
		pthread_mutex_unlock(list->num_eat);
		pthread_mutex_unlock(list->death);
		list = list->next;
	}
}
