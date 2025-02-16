/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahekinci <ahekinci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:41:08 by ahekinci          #+#    #+#             */
/*   Updated: 2025/02/16 14:17:58 by ahekinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

int	monitor_eat_count(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (data->must_eat_count == -1)
		return (0);
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].eat_lock);
		if (data->philos[i].eat_count >= data->must_eat_count)
			count++;
		pthread_mutex_unlock(&data->philos[i].eat_lock);
		i++;
	}
	if (count == data->philo_count)
	{
		pthread_mutex_lock(&data->is_dead_lock);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->is_dead_lock);
		return (1);
	}
	return (0);
}

int	monitor_dead(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_count)
	{
		if (check_dead(&data->philos[i], data->time_to_die))
		{
			print_message("died", &data->philos[i], data->philos[i].id);
			pthread_mutex_lock(&data->is_dead_lock);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->is_dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->start_tv = get_current_time();
	set_data_status(data, 1);
	while (1)
	{
		if (monitor_dead(data))
			break ;
		if (monitor_eat_count(data))
			break ;
	}
	return (NULL);
}

void	set_data_status(t_data *data, int status)
{
	pthread_mutex_lock(&data->status_lock);
	data->status = status;
	pthread_mutex_unlock(&data->status_lock);
}
