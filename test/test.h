#ifndef TEST_H
# define TEST_H
# include <pthread.h>
# include <stdint.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock;
}	t_philo;


typedef struct s_data
{
	int				philo_count;
	pthread_t		*philos;
	

	


}	t_data;

#endif

