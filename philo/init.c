/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahekinci <ahekinci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:39:56 by ahekinci          #+#    #+#             */
/*   Updated: 2025/02/16 14:11:41 by ahekinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

int	init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(data->philo_count * sizeof(pthread_mutex_t));
	if (!forks)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (0);
		i++;
	}
	data->forks = forks;
	return (1);
}

int	init_philos(t_data *data)
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
		philos[i].last_eat_tv = get_current_time();
		if (pthread_mutex_init(&philos[i].eat_lock, NULL))
			return (0);
		philos[i].data = data;
		i++;
	}
	data->philos = philos;
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->forks = NULL;
	data->philos = NULL;
	if (pthread_mutex_init(&data->is_dead_lock, NULL))
		return (0);
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (0);
	if (pthread_mutex_init(&data->status_lock, NULL))
		return (0);
	data->status = 0;
	data->is_dead = 0;
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	if (!init_forks(data) || !init_philos(data))
		return (0);
	return (1);
}
