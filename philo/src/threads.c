/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:59:02 by anshimiy          #+#    #+#             */
/*   Updated: 2022/10/27 00:59:03 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*is_dead(void	*data)
{
	t_philo					*philos;

	philos = (t_philo *)data;
	ft_usleep(philos->philo_arg->time_to_die + 1);
	pthread_mutex_lock(&philos->philo_arg->time_eat);
	pthread_mutex_lock(&philos->philo_arg->finish);
	if (!check_death(philos, 0) && !philos->finish_eat && ((actual_time() - philos->ms_last_eat) \
		>= (long)(philos->philo_arg->time_to_die)))
	{
		pthread_mutex_unlock(&philos->philo_arg->time_eat);
		pthread_mutex_unlock(&philos->philo_arg->finish);
		pthread_mutex_lock(&philos->philo_arg->write_mutex);
		write_status("died\n", philos);
		pthread_mutex_unlock(&philos->philo_arg->write_mutex);
		check_death(philos, 1);
	}
	pthread_mutex_unlock(&philos->philo_arg->time_eat);
	pthread_mutex_unlock(&philos->philo_arg->finish);
	return (NULL);
}

void	*thread_routine(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	if (philos->id % 2 == 0)
		ft_usleep(philos->philo_arg->time_to_eat / 10);
	while (!check_death(philos, 0))
	{
		pthread_create(&philos->thread_death_id, NULL, is_dead, data);
		activity(philos);
		pthread_detach(philos->thread_death_id);
		if ((int)++philos->nb_ate == philos->philo_arg->must_eat)
		{
			pthread_mutex_lock(&philos->philo_arg->finish);
			philos->finish_eat = 1;
			philos->philo_arg->nb_philos_finish_eat++;
			if (philos->philo_arg->nb_philos_finish_eat == philos->philo_arg->total_philos)
			{
				pthread_mutex_unlock(&philos->philo_arg->finish);
				check_death(philos, 2);
			}
			pthread_mutex_unlock(&philos->philo_arg->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->arg.total_philos)
	{
		table->philos[i].philo_arg = &table->arg;
		if (pthread_create(&table->philos[i].thread_id, NULL, thread_routine, &table->philos[i]) != 0)
			return (throw_error("Pthread did not return 0\n", -1));
		i++;
	}
	return (1);
}
