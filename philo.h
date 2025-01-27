#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

// typedef struct timeval	t_tv;

typedef struct s_philo
{
	struct s_data	*data;
	
	pthread_t		thread;
	int				id;
	int				eat_count;
	struct timeval	last_eat_tv;
	
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	struct timeval	start_tv;

	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

int		ft_atoi(const char *str);
time_t	get_deltatime_ms(struct timeval tv);

int		start_simulation(t_data *data);
void	*philo_routine(void *arg);


#endif