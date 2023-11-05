/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:19:33 by markik            #+#    #+#             */
/*   Updated: 2023/07/22 02:02:40 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct philo
{
	int				id;
	pthread_mutex_t	fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	pthread_mutex_t	*num_eat;
	long long		time_to_eat;
	long long		time_to_die;
	long long		time_to_sleep;
	long long		number_eat;
	bool			dead;
	struct philo	*next;
}t_philo;

long long	get_time(void);
int			isspace3(const char *str);
long long	ft_atoll(char *str);
t_philo		*filling_list(t_philo *list, int ac, char **av, int id);
t_philo		*list_maker(int ac, char **av, long long len, int i);
void		my_usleep(t_philo *list, long long n, long long oldt);
void		*routine(void *param);
void		mr_cleaner(t_philo *list);
int			is_degit(char *str);
int			degit(char **av);
int			isnt_zero(char **av);
int			pars_philo(int ac, char **av);
void		clear_list(t_philo *list, pthread_t *Thread, int len);
void		destroy_mutexes(t_philo *list, int len);
pthread_t	*my_threads(t_philo *list, long long len);
int			*filling_tab(long long len);
void		check_death(t_philo *list, int *id, int ac, long long len);
void		routine_part(t_philo *list, long long oldt, long long t);
void		routine_part_two(t_philo *list, long long oldt, long long t);
void		routine_part_third(t_philo *list, long long oldt);
#endif
