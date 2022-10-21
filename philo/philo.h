/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:08:22 by anshimiy          #+#    #+#             */
/*   Updated: 2022/10/21 12:42:46 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_lib/mylib.h"
# include <sys/time.h>

// stop_sig = // 0 if none philosopher is dead, 1 if a philosopher is dead, 2 if all philosophers ate m_eat times
typedef struct s_arg
{
	int						total_philos;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat;
	long int				start_time;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_eat;
	pthread_mutex_t			finish;
	int						nb_philos_finish_eat;
	int						stop_sig; 
}							t_arg;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			left_fork;
	t_arg					*arg;
	long int				ms_last_eat;
	unsigned int			nb_ate;
	int						finish_eat;
}							t_philo;

//  philos = array of philosopher
typedef struct s_table
{
	t_philo					*philos;
	t_arg					arg;
	int						run;
}							t_table;

int				parse_args(int argc, char **argv, t_table *table);
int				ft_exit(char *str);
void			write_status(char *str, t_philo *philos);
long int		actual_time(void);
void			ft_putstright_forkd(char *s, int fd);
void			ft_usleep(long int time_in_ms);
int				init_table(t_table *table);
int				create_thread(t_table *table);
void			activity(t_philo *philos);
int				check_death(t_philo *philos, int i);
#endif