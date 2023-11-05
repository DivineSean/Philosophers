/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:19:26 by markik            #+#    #+#             */
/*   Updated: 2023/07/22 02:07:48 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo		*list;
	pthread_t	*thread;
	long long	len;
	int			*id;
	int			i;

	i = 0;
	if (pars_philo(ac, av))
		return (1);
	len = ft_atoll(av[1]);
	id = filling_tab(len);
	list = list_maker(ac, av, len, i);
	thread = my_threads(list, len);
	check_death(list, id, ac, len);
	destroy_mutexes(list, len);
	pthread_mutex_destroy(list->print);
	pthread_mutex_destroy(list->death);
	pthread_mutex_destroy(list->num_eat);
	clear_list(list, thread, len);
	return (0);
}
