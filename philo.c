#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	philo_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_deltatime_ms(philo->data->start_tv), philo->id);
	// usleep(1000);
}

void	philo_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_deltatime_ms(philo->data->start_tv), philo->id);
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken a fork\n", get_deltatime_ms(philo->data->start_tv), philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taken a fork\n", get_deltatime_ms(philo->data->start_tv), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taken a fork\n", get_deltatime_ms(philo->data->start_tv), philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken a fork\n", get_deltatime_ms(philo->data->start_tv), philo->id);
	}
	// pthread_mutex_lock(philo->left_fork);
	// printf("%ld %d has taken a fork\n", get_deltatime_ms(philo->data->start_tv), philo->id);
	// pthread_mutex_lock(philo->right_fork);
	// printf("%ld %d has taken a fork\n", get_deltatime_ms(philo->data->start_tv), philo->id);
	printf("%ld %d is eating\n", get_deltatime_ms(philo->data->start_tv), philo->id);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->eat_lock);
	gettimeofday(&philo->last_eat_tv, NULL);
	pthread_mutex_unlock(&philo->eat_lock);
	philo->eat_count++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}