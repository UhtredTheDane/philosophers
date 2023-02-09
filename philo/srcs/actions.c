/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:21:42 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/09 18:39:48 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/actions.h"

void drop_forks(t_data *data, int num_fork)
{
    pthread_mutex_unlock(&data->fork);
	pthread_mutex_unlock(&data->philos[num]->data->fork);
}

int    think_action(t_data *data, int num_fork)
{
	long timer;
	int res;

	res = (data->num + 1) % 2;
	timer = get_time_since(data->config->base_time);
	if (!print_log(data, timer, 1))
		return (0);
	if (res)
		pthread_mutex_lock(&data->philos[num_fork]->data->fork);
	else
		pthread_mutex_lock(&data->fork);
	timer = get_time_since(data->config->base_time);
	if(!print_log(data, timer, 2))
	{
		if (res)
			pthread_mutex_unlock(&data->philos[num_fork]->data->fork);
		else
			pthread_mutex_unlock(&data->fork);
		return (0);
	}
	if (res)
		pthread_mutex_lock(&data->fork);
	else
		pthread_mutex_lock(&data->philos[num_fork]->data->fork);
	timer = get_time_since(data->config->base_time);
	if (!print_log(data, timer, 3))
	{
		drop_forks(data, num__fork);
		return (0);
	}
	return (1);
}
 
int eat_action(t_data *data, int num_fork)
{
	long timer;

	pthread_mutex_lock(&data->acces_life_timer);
	data->start_life = get_time_since(data->config->base_time);
	timer = data->start_life;
	++data->nb_eat;
	pthread_mutex_unlock(&data->acces_life_timer);
	if (!print_log(data, timer, 4))
	{	
		drop_forks(data, num_fork);
		return (0);
	}
   	usleep(data->config->time_to_eat * 1000);
	drop_forks(data, num_fork);
	return (1);
}

int    sleep_action(t_data *data)
{
	long timer;

	timer = get_time_since(data->config->base_time);
	if (!print_log(data, timer, 5))
		return (0);
	usleep(data->config->time_to_sleep * 1000);
	return (1);
}
