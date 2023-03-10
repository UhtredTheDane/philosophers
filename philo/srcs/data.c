/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:05:45 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/10 00:54:03 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/data.h"

int	init_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->fork, NULL) != 0)
	{
		printf("Error init mutex %ld\n", data->num);
		free(data);
		return (0);
	}
	if (pthread_mutex_init(&data->acces_life_timer, NULL) != 0)
	{
		printf("Error init mutex %ld\n", data->num);
		pthread_mutex_destroy(&data->fork);
		free(data);
		return (0);
	}
	if (pthread_mutex_init(&data->check_is_alive, NULL) != 0)
	{
		printf("Error init mutex %ld\n", data->num);
		pthread_mutex_destroy(&data->acces_life_timer);
		pthread_mutex_destroy(&data->fork);
		free(data);
		return (0);
	}
	return (1);
}

t_data	*init_data(int num_thread, t_config *config, t_philosopher **philos)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num = num_thread;
	data->start_life = 0;
	data->nb_eat = -1;
	if (config->nb_to_eat != -1)
		data->nb_eat = 0;
	data->is_alive = 1;
	data->philos = philos;
	data->config = config;
	if (!init_data_mutex(data))
	{
		free(data);
		return (NULL);
	}
	return (data);
}

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->fork);
	pthread_mutex_destroy(&data->acces_life_timer);
	pthread_mutex_destroy(&data->check_is_alive);
	free(data);
}
