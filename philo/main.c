/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahekinci <ahekinci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:40:26 by ahekinci          #+#    #+#             */
/*   Updated: 2025/02/07 12:44:18 by ahekinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc, argv))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (!init_data(&data, argc, argv))
	{
		printf("Error: init_data\n");
		if (data.philos)
			free(data.philos);
		if (data.forks)
			free(data.forks);
		return (1);
	}
	if (!create_threads(&data))
	{
		printf("Error: create_threads\n");
		return (free(data.philos), free(data.forks), 1);
	}
	free(data.philos);
	free(data.forks);
	return (0);
}
