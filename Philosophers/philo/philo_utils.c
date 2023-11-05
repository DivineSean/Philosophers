/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:19:23 by markik            #+#    #+#             */
/*   Updated: 2023/07/22 00:29:37 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}

int	isspace3(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 9 && (str[i] <= 13 || str[i] == 32))
			i++;
		else
			break ;
	}
	return (i);
}

long long	ft_atoll(char *str)
{
	long long	res;
	int			signe;
	int			i;

	i = isspace3(str);
	res = 0;
	signe = 1;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			signe = signe * (-1);
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * signe);
}

t_philo	*filling_list(t_philo *list, int ac, char **av, int id)
{
	list->id = id;
	list->dead = false;
	if (ac > 5)
		list->number_eat = ft_atoll(av[5]);
	else
		list->number_eat = -1;
	list->time_to_die = ft_atoll(av[2]);
	list->time_to_eat = ft_atoll(av[3]);
	list->time_to_sleep = ft_atoll(av[4]);
	return (list);
}

t_philo	*list_maker(int ac, char **av, long long len, int i)
{
	t_philo					*list;
	t_philo					*current;
	static pthread_mutex_t	prints;
	static pthread_mutex_t	deaths;
	static pthread_mutex_t	num_eats;

	list = malloc(sizeof(t_philo));
	current = list;
	pthread_mutex_init(&prints, NULL);
	pthread_mutex_init(&deaths, NULL);
	pthread_mutex_init(&num_eats, NULL);
	while (i++ < len)
	{
		current = filling_list(current, ac, av, i);
		pthread_mutex_init(&current->fork, NULL);
		current->print = &prints;
		current->death = &deaths;
		current->num_eat = &num_eats;
		if (i <= len - 1)
		{
			current->next = malloc(sizeof(t_philo));
			current = current->next;
		}
	}
	return (current->next = list, list);
}
