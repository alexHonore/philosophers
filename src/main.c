/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:49:19 by anshimiy          #+#    #+#             */
/*   Updated: 2022/10/20 20:17:20 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death2(t_table *table)
{
	pthread_mutex_lock(&table->arg.dead);
	if (table->arg.stop_sig)
	{
		pthread_mutex_unlock(&table->arg.dead);
		return (1);
	}
	pthread_mutex_unlock(&table->arg.dead);
	return (0);
}

void	stop(t_table *table)
{
	int	i;

	i = -1;
	while (!check_death2(table))
		ft_usleep(1);
	while (++i < table->arg.total_philos)
		pthread_join(table->philos[i].thread_id, NULL);
	pthread_mutex_destroy(&table->arg.write_mutex);
	i = -1;
	while (++i < table->arg.total_philos)
		pthread_mutex_destroy(&table->philos[i].left_fork);
	if (table->arg.stop_sig == 2)
		printf("Each philosopher ate %d time(s)\n", table->arg.must_eat);
	free(table->philos);
}

int main(int argc, char** argv)
{
    t_table table;
    
    if (!(parse_args(argc, argv, &table)))
        return (throw_error("Invalid arguments", 0));
    table.philos = malloc(sizeof(t_philo) * table.arg.total_philos);
    if (!table.philos)
    {
        free(table.philos);
        return (throw_error("Malloc returned NULL", 0));
    }
    //itit shii & create threads
    if (!(init_table(&table)) || !(create_thread(&table)))
    {
        free(table.philos);
        throw_error("Unable to init & create threads", 0);
    }
    stop(&table);
}