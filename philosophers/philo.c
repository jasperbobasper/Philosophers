/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:13:23 by jpfannku          #+#    #+#             */
/*   Updated: 2022/03/10 11:19:44 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->ph_lock);
	philo->thinking = 1;
	pthread_mutex_unlock(&philo->ph_lock);
	return (0);
}

int	pickup_fork(t_philo *philo, int *fork, pthread_mutex_t *fork_mutex)
{
	if (fork_wait(philo, fork, fork_mutex) < 0)
		return (0);
	pthread_mutex_lock(fork_mutex);
	*fork = 1;
	pthread_mutex_unlock(fork_mutex);
	pthread_mutex_lock(&philo->ph_lock);
	philo->pickup++;
	pthread_mutex_unlock(&philo->ph_lock);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->ph_lock);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->ph_lock);
	sleep_loop(philo, philo->table->time_eat);
	pthread_mutex_lock(philo->mutex_left);
	*philo->fork_left = 0;
	pthread_mutex_unlock(philo->mutex_left);
	if (philo->mutex_right)
	{
		pthread_mutex_lock(philo->mutex_right);
		*philo->fork_right = 0;
		pthread_mutex_unlock(philo->mutex_right);
	}
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->ph_lock);
	philo->sleeping = 1;
	pthread_mutex_unlock(&philo->ph_lock);
	sleep_loop(philo, philo->table->time_sleep);
	return (0);
}

void	*philosiphize(void *arg)
{
	t_philo	*philo;
	int		finish;

	finish = -1;
	philo = (t_philo *)arg;
	philo_wait(philo->table, 500);
	if (philo->idx % 2 > 0)
		philo_wait(philo->table, 600);
	while (finish == -1)
	{
		pickup_fork(philo, philo->fork_left, philo->mutex_left);
		pickup_fork(philo, philo->fork_right, philo->mutex_right);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		pthread_mutex_lock(&philo->ph_lock);
		if (philo->finish == 1)
			finish = 1;
		pthread_mutex_unlock(&philo->ph_lock);
	}
	return (NULL);
}
