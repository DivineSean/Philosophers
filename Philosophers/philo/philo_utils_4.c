/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 00:02:34 by markik            #+#    #+#             */
/*   Updated: 2023/07/22 00:02:35 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_part(t_philo *list, long long oldt, long long t)
{
	pthread_mutex_lock(&list->fork);
	pthread_mutex_lock(list->print);
	printf("%lld ms %d has taken fork\n", get_time() - oldt, list->id);
	pthread_mutex_unlock(list->print);
	pthread_mutex_lock(&list->next->fork);
	pthread_mutex_lock(list->print);
	printf("%lld ms %d has taken fork\n", get_time() - oldt, list->id);
	pthread_mutex_unlock(list->print);
	pthread_mutex_lock(list->print);
	printf("%lld ms %d is eating\n", get_time() - oldt, list->id);
	pthread_mutex_unlock(list->print);
	my_usleep(list, list->time_to_eat, t);
}

void	routine_part_two(t_philo *list, long long oldt, long long t)
{
	pthread_mutex_lock(list->print);
	printf("%lld ms %d is sleeping\n", get_time() - oldt, list->id);
	pthread_mutex_unlock(list->print);
	my_usleep(list, list->time_to_sleep, t);
	pthread_mutex_lock(list->print);
	printf("%lld ms %d is thinking\n", get_time() - oldt, list->id);
	pthread_mutex_unlock(list->print);
}

void	routine_part_third(t_philo *list, long long oldt)
{
	long long	t;

	t = get_time();
	pthread_mutex_lock(&list->fork);
	pthread_mutex_lock(list->print);
	printf("%lld ms %d has taken fork\n", get_time() - oldt, list->id);
	pthread_mutex_unlock(list->print);
	my_usleep(list, list->time_to_die * 10, t);
}
