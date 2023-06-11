/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:08:54 by jpfannku          #+#    #+#             */
/*   Updated: 2022/03/09 20:27:53 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_msg(char *str)
{
	printf("%s\n", str);
	return (-1);
}

int	fork_wait(t_philo *philo, int *fork, pthread_mutex_t *lock)
{
	int	end;

	end = 0;
	while (end == 0)
	{
		pthread_mutex_lock(&philo->ph_lock);
		if (philo->finish == 1)
			end = -1;
		pthread_mutex_unlock(&philo->ph_lock);
		if (lock)
		{
			pthread_mutex_lock(lock);
			if (*fork == 0)
			end = 1;
			pthread_mutex_unlock(lock);
		}
	}
	return (end);
}

int	philo_wait(t_table *table, int ms)
{
	long long	time;

	time = 0;
	while (time < ms)
	{
		pthread_mutex_lock(&table->pclock->time_lock);
		time = time_ms(table->pclock->now) - table->start_time;
		pthread_mutex_unlock(&table->pclock->time_lock);
	}
	return (0);
}

int	print_message(t_philo *philo, char *str, int *action, int eat)
{
	long long	now;

	pthread_mutex_lock(&philo->pclock->time_lock);
	now = time_ms(philo->pclock->now);
	pthread_mutex_unlock(&philo->pclock->time_lock);
	printf("%lld Philosopher %i %s\n", now - philo->table->start_time - 500, \
		philo->idx, str);
	if (action)
		*action = 0;
	if (eat == 1)
	{
		philo->last_eat = now;
		philo->meals++;
	}
	return (0);
}

int	solo_philo(t_table *table, t_philo *philo)
{
	pthread_mutex_init(table->fork_mutex, NULL);
	philo->fork_left = table->forks;
	philo->fork_right = NULL;
	philo->mutex_left = table->fork_mutex;
	philo->mutex_right = NULL;
	return (0);
}
