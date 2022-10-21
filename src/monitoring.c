/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:54:29 by anshimiy          #+#    #+#             */
/*   Updated: 2022/10/20 19:58:10 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	write_status(char *str, t_philo *philos)
{
	long int		time;

	time = -1;
	time = actual_time() - philos->arg->start_time;
	if (time >= 0 && time <= 2147483647 && !check_death(philos, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", philos->id, str);
	}
}

void	sleep_think(t_philo *philos)
{
	pthread_mutex_lock(&philos->arg->write_mutex);
	write_status("is sleeping\n", philos);
	pthread_mutex_unlock(&philos->arg->write_mutex);
	ft_usleep(philos->arg->time_to_sleep);
	pthread_mutex_lock(&philos->arg->write_mutex);
	write_status("is thinking\n", philos);
	pthread_mutex_unlock(&philos->arg->write_mutex);
}

void	activity(t_philo *philos)
{
	pthread_mutex_lock(&philos->left_fork);
	pthread_mutex_lock(&philos->arg->write_mutex);
	write_status("has taken a fork\n", philos);
	pthread_mutex_unlock(&philos->arg->write_mutex);
	if (!philos->right_fork)
	{
		ft_usleep(philos->arg->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philos->right_fork);
	pthread_mutex_lock(&philos->arg->write_mutex);
	write_status("has taken a fork\n", philos);
	pthread_mutex_unlock(&philos->arg->write_mutex);
	pthread_mutex_lock(&philos->arg->write_mutex);
	write_status("is eating\n", philos);
	pthread_mutex_lock(&philos->arg->time_eat);
	philos->ms_last_eat = actual_time();
	pthread_mutex_unlock(&philos->arg->time_eat);
	pthread_mutex_unlock(&philos->arg->write_mutex);
	ft_usleep(philos->arg->time_to_eat);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(&philos->left_fork);
	sleep_think(philos);
}
