/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahekinci <ahekinci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:30:40 by ahekinci          #+#    #+#             */
/*   Updated: 2025/02/16 14:19:24 by ahekinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	int	i;

	print_message("is thinking", philo, philo->id);
	i = (philo->data->time_to_die - (philo->data->time_to_sleep
				+ philo->data->time_to_eat)) / 2;
	if (i < 0)
		i = 0;
	ft_usleep(i);
}

void	philo_sleep(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->data->time_to_sleep);
}

static void	philo_lock(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->right_fork);
		print_message("has taken a fork", philo, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_message("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->left_fork);
		print_message("has taken a fork", philo, philo->id);
	}
}

void	philo_eat(t_philo *philo)
{
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message("has taken a fork", philo, philo->id);
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	philo_lock(philo);
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_eat_tv = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_data_status(philo->data) == 0)
		;
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_eat_tv = get_current_time();
	pthread_mutex_unlock(&philo->eat_lock);
	if (philo->id % 2)
		ft_usleep(1);
	while (!check_is_dead(philo->data))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}


int	get_data_status(t_data *data)
{
	int status;

	pthread_mutex_lock(&data->status_lock);
	status = data->status;
	pthread_mutex_unlock(&data->status_lock);
	return (status);
}

