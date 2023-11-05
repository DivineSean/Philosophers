/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:18:26 by markik            #+#    #+#             */
/*   Updated: 2023/07/22 01:18:27 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	one_philo(t_philo *list, sem_t *fork, long long oldt)
{
	long long	t;

	t = get_time();
	sem_wait(fork);
	sem_wait(list->print);
	printf("%lld ms %d has taken fork\n", get_time() - oldt, list->id);
	sem_post(list->print);
	my_usleep(list, list->time_to_die * 10, t);
	exit(1);
}

void	routine_part(t_philo *list, sem_t *fork, long long oldt, long long t)
{
	sem_wait(fork);
	sem_wait(list->print);
	printf("%lld ms %d has taken fork\n", get_time() - oldt, list->id);
	sem_post(list->print);
	sem_wait(fork);
	sem_wait(list->print);
	printf("%lld ms %d has taken fork\n", get_time() - oldt, list->id);
	sem_post(list->print);
	sem_wait(list->print);
	printf("%lld ms %d is eating\n", get_time() - oldt, list->id);
	sem_post(list->print);
	my_usleep(list, list->time_to_eat, t);
}

void	routine_part_two(t_philo *list, long long t, long long oldt)
{
	sem_wait(list->print);
	printf("%lld ms %d is sleeping\n", get_time() - oldt, list->id);
	sem_post(list->print);
	my_usleep(list, list->time_to_sleep, t);
	sem_wait(list->print);
	printf("%lld ms %d is thinking\n", get_time() - oldt, list->id);
	sem_post(list->print);
}

void	*routine(void *param, sem_t *fork)
{
	t_philo		*list;
	long long	oldt;
	long long	t;

	oldt = get_time();
	list = (t_philo *)param;
	if (list->next->id == list->id)
		one_philo(list, fork, oldt);
	while (list->number_eat)
	{
		t = get_time();
		routine_part(list, fork, oldt, t);
		t = get_time();
		sem_post(fork);
		sem_post(fork);
		sem_wait(list->num_eat);
		list->number_eat--;
		sem_post(list->num_eat);
		routine_part_two(list, t, oldt);
	}
	return (exit(0), NULL);
}

void	my(pid_t *pid, int len)
{
	int	i;
	int	status;

	if (len == 0)
		return ;
	status = 0;
	while (waitpid(-1, &status, 0) == -1)
		;
	if (status == 0)
		my(pid, --len);
	else
	{
		i = 0;
		while (i < len)
			kill(pid[i++], SIGKILL);
	}
	return ;
}
