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

void drop_forks(t_data *data, int num)
{
    pthread_mutex_unlock(&data->right_fork);
	pthread_mutex_unlock(&data->philos[num]->data->right_fork);
}

int    think_action(t_data *data, int num_left_fork)
{
	long timer;

	timer = get_time_since(data->config->base_time);
	if (!print_log(data, timer, 1))
		return (0);
	pthread_mutex_lock(&data->right_fork);
	timer = get_time_since(data->config->base_time);
	if(!print_log(data, timer, 2))
	{
		pthread_mutex_unlock(&data->right_fork);
		return (0);
	}
	pthread_mutex_lock(&data->philos[num_left_fork]->data->right_fork);
	timer = get_time_since(data->config->base_time);
	if (!print_log(data, timer, 3))
	{
		drop_forks(data, num_left_fork);
		return (0);
	}
	return (1);
}
 
int eat_action(t_data *data, int num_left_fork)
{
	long timer;

	pthread_mutex_lock(&data->acces_life_timer);
	data->start_life = get_time_since(data->config->base_time);
	timer = data->start_life;
	++data->nb_eat;
	pthread_mutex_unlock(&data->acces_life_timer);
	if (!print_log(data, timer, 4))
	{	
		drop_forks(data, num_left_fork);
		return (0);
	}
   	usleep(data->config->time_to_eat * 1000);
	drop_forks(data, num_left_fork);
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
