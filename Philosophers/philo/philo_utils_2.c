/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:19:16 by markik            #+#    #+#             */
/*   Updated: 2023/07/22 02:07:00 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_degit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

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

void	clear_list(t_philo *list, pthread_t *Thread, int len)
{
	t_philo	*head;
	int		i;

	head = list;
	i = 1;
	while (i < len)
	{
		head = head->next;
		i++;
	}
	head->next = NULL;
	mr_cleaner(list);
	free(Thread);
}
