/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:18:56 by markik            #+#    #+#             */
/*   Updated: 2023/07/21 23:48:11 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(t_philo *list, long long n, long long oldt)
{
	long long	t;

	t = get_time();
	while (get_time() - t <= n)
	{
		if (get_time() - oldt >= list->time_to_die)
		{
			pthread_mutex_lock(list->print);
			printf("%lld ms %d is dead\n", get_time() - oldt, list->id);
			pthread_mutex_lock(list->death);
			list->dead = true;
			pthread_mutex_unlock(list->death);
		}
	}
	return ;
}

void	mr_cleaner(t_philo *list)
{
	if (!(list))
		return ;
	if ((list)->next)
		mr_cleaner((list)->next);
	free(list);
	list = NULL;
}

void	*routine(void *param)
{
	long long	oldt;
	long long	t;
	t_philo		*list;

	list = (t_philo *)param;
	oldt = get_time();
	if (list->next->id == list->id)
		return (routine_part_third(list, oldt), NULL);
	if (list->id % 2 == 0)
		usleep(500);
	while (list->number_eat)
	{
		t = get_time();
		routine_part(list, oldt, t);
		t = get_time();
		pthread_mutex_unlock(&list->fork);
		pthread_mutex_unlock(&list->next->fork);
		pthread_mutex_lock(list->num_eat);
		list->number_eat--;
		pthread_mutex_unlock(list->num_eat);
		routine_part_two(list, oldt, t);
	}
	return (NULL);
}
