/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:53:22 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/11 21:52:37 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reaper.h"

int	is_satisfied(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->acces_life_timer);
	res = data->config->nb_to_eat == data->nb_eat;
	pthread_mutex_unlock(&data->acces_life_timer);
	return (res);
}

int	is_all_satisfied(t_data *data, int all_satisfied)
{
	int i;
	if (all_satisfied)
	{
		i = 0;
		while (i < data->config->nb_of_philo)
		{
			pthread_mutex_lock(&data->philos[i]->data->check_is_alive);
			data->philos[i]->data->is_alive = 0;
			pthread_mutex_unlock(&data->philos[i]->data->check_is_alive);
			++i;
		}
		return (1);
	}
	return (0);
}

int	is_not_dead(t_data *data, long timer)
{
	int	i;

	pthread_mutex_lock(&data->acces_life_timer);
	if (timer > data->start_life + data->config->time_to_die)
	{
		pthread_mutex_unlock(&data->acces_life_timer);
		i = 0;
		while (i < data->config->nb_of_philo)
		{
			pthread_mutex_lock(&data->philos[i]->data->check_is_alive);
			data->philos[i]->data->is_alive = 0;
			pthread_mutex_unlock(&data->philos[i]->data->check_is_alive);
			++i;
		}
		print_log(data, timer, 0);
		return (0);
	}
	pthread_mutex_unlock(&data->acces_life_timer);
	return (1);
}

int	check_death(t_philosopher **philos, int all_satisfied)
{
	int	i;
	int	nb_of_philo;
	int	timer;

	i = 0;
	nb_of_philo = philos[0]->data->config->nb_of_philo;
	while (i < nb_of_philo)
	{
		timer = get_time_since(&philos[i]->data->config->base_time);
		if (!is_not_dead(philos[i]->data, timer))
			return (0);
		if (all_satisfied)
			all_satisfied = is_satisfied(philos[i]->data);
		++i;
	}
	if (is_all_satisfied(philos[0]->data, all_satisfied))
		return (0);
	return (1);
}

void	*reaper_life(void *arg)
{
	t_philosopher	**philos;
	int				alive;

	philos = (t_philosopher **) arg;
	alive = 1;
	while (alive)
	{
		usleep(2000);
		if (!check_death(philos, philos[0]->data->config->nb_to_eat))
			alive = 0;
	}
	return (NULL);
}
