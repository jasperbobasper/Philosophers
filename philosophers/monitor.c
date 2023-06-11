/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:36:43 by jpfannku          #+#    #+#             */
/*   Updated: 2022/03/10 11:26:24 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_table *table)
{
	int	fin;

	fin = 0;
	philo_wait(table, 300);
	while (fin == 0)
		fin = check_status(table, table->philo);
	return (fin);
}

int	check_status(t_table *table, t_philo *philo)
{
	int				i;
	long long		now;

	i = 0;
	while (philo[i].idx != -1)
	{
		pthread_mutex_lock(&table->pclock->time_lock);
		now = time_ms(table->pclock->now);
		pthread_mutex_unlock(&table->pclock->time_lock);
		if (now - philo[i].last_eat > table->time_die)
		{
			set_finish(table, philo, 1);
			printf("%lld Philosopher %i died\n", now - table->start_time \
				- 500, philo[i].idx);
			return (2);
		}
		if (philo->meals == table->num_times)
		{
			if (set_finish(table, philo, 0) == 0)
				return (2);
		}
		print_action(&philo[i]);
		i++;
	}
	return (0);
}

int	print_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->ph_lock);
	if (philo->thinking == 1)
		print_message(philo, "is thinking", &philo->thinking, 0);
	while (philo->pickup > 0)
	{
		print_message(philo, "has taken a fork", NULL, 0);
		philo->pickup--;
	}
	if (philo->eating == 1)
		print_message(philo, "is eating", &philo->eating, 1);
	if (philo->sleeping == 1)
		print_message(philo, "is sleeping", &philo->sleeping, 0);
	pthread_mutex_unlock(&philo->ph_lock);
	return (0);
}

int	set_finish(t_table *table, t_philo *philo, int dead)
{
	int	i;
	int	mark;

	i = 0;
	mark = 0;
	while (philo[i].idx != -1)
	{
		if ((table->num_times > 0 && philo[i].meals < \
			table->num_times) && dead == 0)
			mark = 1;
		else
		{
			pthread_mutex_lock(&philo[i].ph_lock);
			philo[i].finish = 1;
			pthread_mutex_unlock(&philo[i].ph_lock);
		}
		i++;
	}
	return (mark);
}

void	*philo_clock(void *arg)
{
	t_pclock	*pclock;
	int			finish;

	pclock = (t_pclock *)arg;
	finish = 0;
	while (finish == 0)
	{
		pthread_mutex_lock(&pclock->time_lock);
		gettimeofday(&pclock->now, NULL);
		if (pclock->finish == 1)
			finish = 1;
		pthread_mutex_unlock(&pclock->time_lock);
	}
	return (NULL);
}
