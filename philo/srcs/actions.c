/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:21:42 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/12 15:33:16 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/actions.h"

void	lock_good_fork(t_data *data, int num_fork, int res, int order)
{
	if (res)
	{
		if (!order)
			pthread_mutex_lock(&data->philos[num_fork]->data->fork);
		else
			pthread_mutex_lock(&data->fork);
	}
	else
	{
		if (!order)
			pthread_mutex_lock(&data->fork);
		else
			pthread_mutex_lock(&data->philos[num_fork]->data->fork);
	}
}

int	think_action(t_data *data, int num_fork)
{
	int	res;

	res = (data->num + 1) % 2;
	if (!print_log(data, 1))
		return (0);
	lock_good_fork(data, num_fork, res, 0);
	if (data->config->nb_of_philo <= 1)
		return (0);
	if (!print_log(data, 2))
	{
		if (res)
			pthread_mutex_unlock(&data->philos[num_fork]->data->fork);
		else
			pthread_mutex_unlock(&data->fork);
		return (0);
	}
	lock_good_fork(data, num_fork, res, 1);
	if (!print_log(data, 2))
	{
		drop_forks(data, num_fork);
		return (0);
	}
	return (1);
}

void	ft_sleep(t_config *config, long time)
{
	long	start;
	long	timer;

	start = get_time_since(&config->base_time);
	timer = start;
	while (timer < start + time)
	{
		usleep(250);
		timer = get_time_since(&config->base_time);
	}
}

int	eat_action(t_data *data, int num_fork)
{
	pthread_mutex_lock(&data->acces_life_timer);
	data->start_life = get_time_since(&data->config->base_time);
	if (data->config->nb_to_eat != -1)
		++(data->nb_eat);
	pthread_mutex_unlock(&data->acces_life_timer);
	if (!print_log(data, 3))
	{	
		drop_forks(data, num_fork);
		return (0);
	}
	ft_sleep(data->config, data->config->time_to_eat);
	return (1);
}

int	sleep_action(t_data *data, int num_fork)
{
	if (!print_log(data, 4))
	{
		drop_forks(data, num_fork);
		return (0);
	}
	drop_forks(data, num_fork);
	ft_sleep(data->config, data->config->time_to_sleep);
	return (1);
}
