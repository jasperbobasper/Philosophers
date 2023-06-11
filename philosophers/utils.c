/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:42:55 by jpfannku          #+#    #+#             */
/*   Updated: 2022/03/15 12:02:23 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	val;
	int	x;
	int	neg;

	val = 0;
	x = 0;
	neg = 1;
	while ((str[x] >= 9 && str[x] <= 13) || str[x] == 32 || str[x] == '+')
		x++;
	if (str[x] == '-')
	{
		neg = -1;
		x++;
	}
	while (str[x] >= '0' && str[x] <= '9')
	{
		val = val * 10 + str[x] - 48;
		x++;
	}
	if (str[x] != 0)
		return (0);
	return (val * neg);
}

long long	time_ms(struct timeval time)
{
	long long	ms;

	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}

void	*ft_calloc(size_t sz, int len)
{
	void	*mem;

	mem = malloc(sz * len);
	memset(mem, 0, sz * len);
	return (mem);
}

int	check_table(int argc, t_table *table)
{
	if (table->num_philo > 0 && table->time_die > 0 && \
		table->time_eat > 0 && table->time_sleep > 0)
	{
		if ((argc == 6 && table->num_times > 0) || argc == 5)
			return (0);
	}
	free(table);
	return (-1);
}

int	sleep_loop(t_philo *philo, long long time_action)
{
	int				finish;
	struct timeval	now;

	finish = 0;
	gettimeofday(&now, NULL);
	while (finish == 0)
	{
		usleep(500);
		pthread_mutex_lock(&philo->pclock->time_lock);
		if (time_ms(philo->pclock->now) - time_ms(now) \
			> time_action)
			finish = 1;
		pthread_mutex_unlock(&philo->pclock->time_lock);
	}
	return (0);
}
