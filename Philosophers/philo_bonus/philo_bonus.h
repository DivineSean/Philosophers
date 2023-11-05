/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 00:37:56 by markik            #+#    #+#             */
/*   Updated: 2023/07/22 02:08:56 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <signal.h>

typedef struct philo
{
	int				id;
	sem_t			*print;
	sem_t			*num_eat;
	long long		time_to_eat;
	long long		time_to_die;
	long long		time_to_sleep;
	long long		number_eat;
	struct philo	*next;
}t_philo;

long long	ft_atoll(char *str);
long long	get_time(void);
void		lets_fork(t_philo *list, sem_t *forshit, long long len);
void		check_sem_fail(t_philo *list, sem_t *prints, sem_t *num_eats);
int			isspace3(const char *str);
t_philo		*filling_list(t_philo *list, int ac, char **av, int id);
int			is_degit(char *str);
int			degit(char **av);
int			isnt_zero(char **av);
int			pars_philo(int ac, char **av);
void		my_usleep(t_philo *list, long long n, long long oldt);
t_philo		*list_maker(int ac, char **av, long long len, int i);
void		one_philo(t_philo *list, sem_t *fork, long long oldt);
void		routine_part(t_philo *list, sem_t *fork, \
		long long oldt, long long t);
void		routine_part_two(t_philo *list, long long t, long long oldt);
void		*routine(void *param, sem_t *fork);
void		my(pid_t *pid, int len);
#endif
