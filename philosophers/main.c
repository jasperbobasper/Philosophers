/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:17:31 by jpfannku          #+#    #+#             */
/*   Updated: 2022/03/09 15:03:58 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers(int argc, char **argv)
{
	t_table	*table;

	table = init_table(argc, argv);
	if (!table)
		return (0);
	init_philos(table->philo, table);
	if (init_philo_threads(table) < 0)
		return (free_table(table));
	monitoring(table);
	destroy_philos(table);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc >= 5 && argc < 7)
		philosophers(argc, argv);
	return (0);
}
