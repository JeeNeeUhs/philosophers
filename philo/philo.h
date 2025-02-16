/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahekinci <ahekinci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:37:59 by ahekinci          #+#    #+#             */
/*   Updated: 2025/02/16 16:06:56 by ahekinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	int				id;
	int				eat_count;
	size_t			last_eat_tv;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_data
{
	int				status;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	size_t			start_tv;
	int				is_dead;
	pthread_mutex_t	status_lock;
	pthread_mutex_t	is_dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

// check.c
int		check_args(int argc, char **argv);
int		check_dead(t_philo *philo, size_t die_time);
int		check_is_dead(t_data *data);
int		check_is_in_int(char *str);

// create.c
int		create_threads(t_data *data);

// init.c
int		init_data(t_data *data, int argc, char **argv);
int		init_forks(t_data *data);
int		init_philos(t_data *data);

// monitor.c
int		monitor_dead(t_data *data);
int		monitor_eat_count(t_data *data);
void	*monitor(void *arg);
void	set_data_status(t_data *data, int status);
int		get_data_status(t_data *data);

// philo.c
void	*philo_loop(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

// utils.c
int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
void	print_message(char *str, t_philo *philo, int id);

#endif
