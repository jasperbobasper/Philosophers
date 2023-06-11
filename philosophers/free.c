/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:40:10 by jpfannku          #+#    #+#             */
/*   Updated: 2022/03/10 11:21:59 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_philos(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = table->philo;
	while (i < table->num_philo)
	{
		if (pthread_join(table->philo[i].ph_thread, NULL) != 0)
			return (exit_msg("failed to join thread"));
		i++;
	}
	pthread_mutex_lock(&table->pclock->time_lock);
	table->pclock->finish = 1;
	pthread_mutex_unlock(&table->pclock->time_lock);
	if (pthread_join(table->pclock->philo_time, NULL) != 0)
		return (exit_msg("failed to join thread"));
	destroy_mutex(table);
	return (free_table(table));
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->pclock->time_lock);
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->fork_mutex[i]);
		pthread_mutex_destroy(&table->philo[i].ph_lock);
		i++;
	}
}

int	free_table(t_table	*table)
{
	free(table->philo);
	free(table->fork_mutex);
	free(table->forks);
	free(table->pclock);
	free(table);
	return (0);
}
