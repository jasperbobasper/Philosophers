/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:58:21 by jpfannku          #+#    #+#             */
/*   Updated: 2022/03/09 19:12:04 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_table
{
	long long		start_time;
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_times;
	struct s_philo	*philo;
	int				*forks;
	pthread_mutex_t	*fork_mutex;
	struct s_pclock	*pclock;
}	t_table;

typedef struct s_philo
{
	long long		last_eat;
	int				idx;
	int				meals;
	int				finish;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_right;
	int				*fork_right;
	int				*fork_left;
	pthread_t		ph_thread;
	pthread_mutex_t	ph_lock;
	struct s_table	*table;
	struct s_pclock	*pclock;
	int				eating;
	int				sleeping;
	int				thinking;
	int				pickup;
}	t_philo;

typedef struct s_pclock
{
	pthread_t		philo_time;
	int				finish;
	struct timeval	now;
	pthread_mutex_t	time_lock;
}	t_pclock;

int			philosophers(int argc, char **argv);

/*initialise*/
t_table		*init_table(int argc, char **argv);
int			table_mem(t_table *table);
void		init_forks(t_philo *philo, t_table *table);
void		init_philos(t_philo	*philo, t_table *table);
int			init_philo_threads(t_table *table);
int			solo_philo(t_table *table, t_philo *philo);

/*monitor*/
int			monitoring(t_table *table);
int			check_status(t_table *table, t_philo *philo);
int			print_action(t_philo *philo);
int			set_finish(t_table *table, t_philo *philo, int dead);
void		*philo_clock(void *arg);

/*philosopher actions*/
void		*philosiphize(void *arg);
int			philo_sleep(t_philo *philo);
int			philo_eat(t_philo *philo);
int			pickup_fork(t_philo *philo, int *fork, pthread_mutex_t *fork_mutex);
int			philo_think(t_philo *philo);
int			sleep_loop(t_philo	*philo, long long time_action);
int			fork_wait(t_philo *philo, int *fork, pthread_mutex_t *lock);
int			philo_wait(t_table *table, int ms);

/*utils*/
int			ft_atoi(const char *str);
void		*ft_calloc(size_t sz, int len);
long long	time_ms(struct timeval time);
int			check_table(int argc, t_table *table);
int			exit_msg(char *str);
int			print_message(t_philo *philo, char *str, int *action, int eat);

/*free*/
int			destroy_philos(t_table *table);
int			free_table(t_table	*table);
void		destroy_mutex(t_table *table);

#endif