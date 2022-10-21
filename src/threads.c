/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:20:39 by anshimiy          #+#    #+#             */
/*   Updated: 2022/10/21 15:29:11 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*is_dead(void	*data)
{
	t_philo					*philos;

	philos = (t_philo *)data;
	ft_usleep(philos->arg->time_to_die + 1);
	pthread_mutex_lock(&philos->arg->time_eat);
	pthread_mutex_lock(&philos->arg->finish);
	if (!check_death(philos, 0) && !philos->finish_eat && ((actual_time() - philos->ms_last_eat) \
		>= (long)(philos->arg->time_to_die)))
	{
		pthread_mutex_unlock(&philos->arg->time_eat);
		pthread_mutex_unlock(&philos->arg->finish);
		pthread_mutex_lock(&philos->arg->write_mutex);
		write_status("died\n", philos);
		pthread_mutex_unlock(&philos->arg->write_mutex);
		check_death(philos, 1);
	}
	pthread_mutex_unlock(&philos->arg->time_eat);
	pthread_mutex_unlock(&philos->arg->finish);
	return (NULL);
}

void	*thread(void *data)
{
    t_philo     *philo;

    philo = (t_philo *)data;
    if (philo->id % 2 == 0)
		ft_usleep(philo->arg->time_to_eat / 10);
	while (!check_death(philo, 0))
	{
		pthread_create(&philo->thread_death_id, NULL, is_dead, data);
		activity(philo);
		pthread_detach(philo->thread_death_id);
		if ((int)++philo->nb_ate == philo->arg->must_eat)
		{
			pthread_mutex_lock(&philo->arg->finish);
			philo->finish_eat = 1;
			philo->arg->nb_philos_finish_eat++;
			if (philo->arg->nb_philos_finish_eat == philo->arg->total_philos)
			{
				pthread_mutex_unlock(&philo->arg->finish);
				check_death(philo, 2);
			}
			pthread_mutex_unlock(&philo->arg->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	create_thread(t_table *table)
{
    int i;

    i = 0;
    while (i < table->arg.total_philos && table->arg.stop_sig == 0)
    {
		//printf("\n\n--- %d ---\n\n", table->arg.stop_sig);
		//ft_usleep(10);
        table->philos[i].arg = &table->arg;
        if (pthread_create(&table->philos[i].thread_id, NULL, thread, &table->philos[i]) != 0)
            return (throw_error("Cannot create threads", 0));
        i++;
    }
    return (1);   
}