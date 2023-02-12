/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:11:26 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/12 15:20:33 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	drop_forks(t_data *data, int num_fork)
{
	pthread_mutex_unlock(&data->fork);
	pthread_mutex_unlock(&data->philos[num_fork]->data->fork);
}

long	get_time_since(struct timeval *base_time)
{
	struct timeval	present_time;
	unsigned long	s_nb;
	unsigned long	micro_nb;

	gettimeofday(&present_time, NULL);
	s_nb = (present_time.tv_sec - base_time->tv_sec) * 1000000;
	micro_nb = present_time.tv_usec - base_time->tv_usec;
	return ((s_nb + micro_nb) / 1000);
}

void	print_death(t_data *data)
{
	long	timer;

	timer = get_time_since(&data->config->base_time);
	printf("%ld ms %ld died\n", timer, data->num + 1);
	pthread_mutex_unlock(&data->config->acces_printer);
}

int	print_log(t_data *data, int type)
{
	long	timer;

	pthread_mutex_lock(&data->config->acces_printer);
	if (type == 0)
	{
		print_death(data);
		return (1);
	}
	if (is_anyone_dead(data))
	{
		pthread_mutex_unlock(&data->config->acces_printer);
		return (0);
	}
	timer = get_time_since(&data->config->base_time);
	if (type == 1)
		printf("%ld ms %ld is thinking\n", timer, data->num + 1);
	else if (type == 2)
		printf("%ld ms %ld has taken a fork\n", timer, data->num + 1);
	else if (type == 3)
		printf("%ld ms %ld is eating\n", timer, data->num + 1);
	else if (type == 4)
		printf("%ld ms %ld is sleeping\n", timer, data->num + 1);
	pthread_mutex_unlock(&data->config->acces_printer);
	return (1);
}
