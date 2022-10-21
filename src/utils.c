/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:17:49 by anshimiy          #+#    #+#             */
/*   Updated: 2022/10/12 17:07:27 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// check t_arg comments
int	check_death(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos->arg->dead);
	if (i)
		philos->arg->stop_sig = i;
	if (philos->arg->stop_sig)
	{
		pthread_mutex_unlock(&philos->arg->dead);
		return (1);
	}
	pthread_mutex_unlock(&philos->arg->dead);
	return (0);
}

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		throw_error("Gettimeofday returned -1", 0);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
