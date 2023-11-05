/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:18:35 by markik            #+#    #+#             */
/*   Updated: 2023/07/22 02:13:14 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	mr_cleaner(t_philo *list)
{
	if (!(list))
		return ;
	if ((list)->next)
		mr_cleaner((list)->next);
	free(list);
	list = NULL;
}

void	clear_list(t_philo *list, int len)
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
}

void	check_sem_fail(t_philo *list, sem_t *prints, sem_t *num_eats)
{
	if (prints == SEM_FAILED || num_eats == SEM_FAILED)
	{
		printf("sem_open failled!\n");
		free(list);
		exit(1);
	}
}

void	lets_fork(t_philo *list, sem_t *forshit, long long len)
{
	pid_t	*pid;
	int		i;

	pid = malloc(sizeof(pid_t) * len);
	i = 0;
	while (i < len)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			routine(list, forshit);
		list = list->next;
		i++;
	}
	my(pid, len);
	free(pid);
	sem_close(forshit);
	sem_close(list->print);
}

int	main(int ac, char **av)
{
	t_philo		*list;
	sem_t		*forshit;
	long long	len;
	int			i;

	i = 0;
	if (pars_philo(ac, av))
		exit(1);
	len = ft_atoll(av[1]);
	list = list_maker(ac, av, len, i);
	sem_unlink("/fork");
	forshit = sem_open("/fork", O_CREAT, 0777, len);
	if (forshit == SEM_FAILED)
		return (printf("sem_open failled!!\n"), exit(1), 0);
	lets_fork(list, forshit, len);
	clear_list(list, len);
	return (0);
}
