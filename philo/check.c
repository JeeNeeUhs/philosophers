/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahekinci <ahekinci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:39:44 by ahekinci          #+#    #+#             */
/*   Updated: 2025/02/07 12:41:32 by ahekinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		if (check_is_in_int(argv[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

int	check_dead(t_philo *philo, size_t die_time)
{
	pthread_mutex_lock(&philo->eat_lock);
	if (get_current_time() - philo->last_eat_tv > die_time)
	{
		pthread_mutex_unlock(&philo->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_lock);
	return (0);
}

int	check_is_dead(t_data *data)
{
	pthread_mutex_lock(&data->is_dead_lock);
	if (data->is_dead)
	{
		pthread_mutex_unlock(&data->is_dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->is_dead_lock);
	return (0);
}

int	check_is_in_int(char *str)
{
	long	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
		if (res > 2147483647)
			return (-1);
	}
	return ((int)res);
}
