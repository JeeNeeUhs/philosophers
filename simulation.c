#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

static int	init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(data->philo_count * sizeof(pthread_mutex_t));
	if (!forks)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	data->forks = forks;
	return (1);
}

static int	init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!philos)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		philos[i].id = i;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		philos[i].eat_count = 0;
		gettimeofday(&philos[i].last_eat_tv, NULL);
		pthread_mutex_init(&philos[i].last_eat_lock, NULL);
		philos[i].data = data;
		i++;
	}
	data->philos = philos;
	return (1);
}

static void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		if (i == data->philo_count)
			i = 0;
		pthread_mutex_lock(&data->philos[i].last_eat_lock);
		if (get_deltatime_ms(data->philos[i].last_eat_tv) > data->time_to_die)
		{
			printf("%ld %d died\n", get_deltatime_ms(data->start_tv), data->philos[i].id);
			pthread_mutex_lock(&data->is_dead_lock);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->is_dead_lock);
			pthread_mutex_unlock(&data->philos[i].last_eat_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->philos[i].last_eat_lock);
		i++;
	}
	return (NULL);
}

// void	*check_dead(void *arg)
// {
// 	t_data	*data;
// 	int		i;

// 	data = (t_data *)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->is_dead_lock);


// 	}
// }

int	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;
	int	i;

	if (!init_forks(data))
		return (0);
	if (!init_philos(data))
		return (0);
	gettimeofday(&data->start_tv, NULL);
	pthread_create(&monitor_thread, NULL, monitor, data);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
}