/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:32:02 by jpfannku          #+#    #+#             */
/*   Updated: 2022/03/09 20:19:31 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = ft_calloc(sizeof(t_table), 1);
	if (!table)
		return (NULL);
	table->num_philo = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	table->num_times = -1;
	if (argc > 5)
		table->num_times = ft_atoi(argv[5]);
	if (check_table(argc, table) < 0)
		return (NULL);
	if (table_mem(table) < 0)
		return (NULL);
	pthread_mutex_init(&table->pclock->time_lock, NULL);
	init_philos(table->philo, table);
	return (table);
}

int	table_mem(t_table *table)
{
	table->philo = ft_calloc(sizeof(t_philo), table->num_philo + 1);
	table->fork_mutex = ft_calloc(sizeof(pthread_mutex_t), table->num_philo);
	table->forks = ft_calloc(sizeof(int), table->num_philo);
	table->pclock = ft_calloc(sizeof(t_pclock), 1);
	if (!table->philo || !table->fork_mutex || !table->forks || !table->pclock)
	{
		free(table);
		return (exit_msg("Malloc fail"));
	}
	return (1);
}

void	init_forks(t_philo *philo, t_table *table)
{
	int		i;

	i = 0;
	if (table->num_philo == 1)
		solo_philo(table, philo);
	else
	{
		while (i < table->num_philo)
		{
			pthread_mutex_init(&table->fork_mutex[i], NULL);
			philo[i].mutex_right = &table->fork_mutex[i];
			philo[i].fork_right = &table->forks[i];
			if (i != 0)
			{
				philo[i].mutex_left = &table->fork_mutex[i - 1];
				philo[i].fork_left = &table->forks[i - 1];
			}
			i++;
		}
		philo[0].mutex_left = &table->fork_mutex[i - 1];
		philo[0].fork_left = &table->forks[i - 1];
	}
}

void	init_philos(t_philo	*philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_init(&philo[i].ph_lock, NULL);
		philo[i].idx = i + 1;
		philo[i].finish = -1;
		philo[i].table = table;
		philo[i].pclock = table->pclock;
		philo[i].meals = 0;
		i++;
	}
	philo[i].idx = -1;
	philo[i].finish = 1;
	init_forks(philo, table);
}

int	init_philo_threads(t_table *table)
{
	int			i;
	t_philo		*philo;

	philo = table->philo;
	i = 0;
	gettimeofday(&table->pclock->now, NULL);
	table->start_time = time_ms(table->pclock->now);
	if (pthread_create(&table->pclock->philo_time, NULL, &philo_clock, \
		(void *)table->pclock) != 0)
		return (exit_msg("failed to create thread"));
	while (i < table->num_philo)
	{
		philo[i].last_eat = table->start_time + 500;
		if (pthread_create(&philo[i].ph_thread, NULL, &philosiphize, &philo[i]) \
			!= 0)
			return (exit_msg("failed to create thread"));
		i++;
	}
	return (0);
}
