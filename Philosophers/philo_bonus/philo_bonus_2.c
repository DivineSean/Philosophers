/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:18:29 by markik            #+#    #+#             */
/*   Updated: 2023/07/22 01:28:23 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	degit(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!is_degit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	isnt_zero(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoll(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	pars_philo(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("incorrect input!!\n"), 1);
	else if (!degit(av))
		return (printf("the arguments should be degit (sign allown't)!!\n"), 2);
	else if (!isnt_zero(av))
		return (printf("incorrect input 0!!\n"), 3);
	return (0);
}

void	my_usleep(t_philo *list, long long n, long long oldt)
{
	long long	t;

	t = get_time();
	while (get_time() - t < n)
	{
		if (get_time() - oldt >= list->time_to_die)
		{
			sem_wait(list->print);
			printf("%lld ms %d is dead\n", get_time() - oldt, list->id);
			exit(1);
		}
	}
	return ;
}

t_philo	*list_maker(int ac, char **av, long long len, int i)
{
	t_philo			*list;
	t_philo			*current;
	static sem_t	*prints;
	static sem_t	*num_eats;

	sem_unlink("/print");
	sem_unlink("/numeats");
	prints = sem_open("/print", O_CREAT, 0777, 1);
	num_eats = sem_open("/numeats", O_CREAT, 0777, 1);
	list = malloc(sizeof(t_philo));
	current = list;
	check_sem_fail(list, prints, num_eats);
	while (i++ < len)
	{
		current = filling_list(current, ac, av, i);
		current->print = prints;
		current->num_eat = num_eats;
		if (i <= len - 1)
		{
			current->next = malloc(sizeof(t_philo));
			current = current->next;
		}
	}
	return (current->next = list, list);
}
