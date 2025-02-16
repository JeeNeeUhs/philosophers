/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahekinci <ahekinci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:39:52 by ahekinci          #+#    #+#             */
/*   Updated: 2025/02/16 14:13:20 by ahekinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, philo_loop, (void *)&data->philos[i]))
			return (0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, (void *)data))
		return (0);
	if (pthread_join(monitor_thread, NULL))
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (0);
		i++;
	}
	return (1);
}
