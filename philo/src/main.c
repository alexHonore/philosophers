/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:59:09 by anshimiy          #+#    #+#             */
/*   Updated: 2022/10/27 00:59:10 by anshimiy         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_table		table;

	if (!(parse_args(argc, argv, &table)))
		return (throw_error("Invalid Arguments\n", -1));
	table.philos = malloc(sizeof(t_philo) * table.arg.total_philos);
	if (!table.philos)
		return (throw_error("Malloc returned NULL\n", -1));
	if (!init_table(&table) || !create_threads(&table))
	{
		free(table.philos);
		return (0);
	}
	stop(&table);
}
