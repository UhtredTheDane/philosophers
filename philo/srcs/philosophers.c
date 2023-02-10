/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:12:06 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/10 16:17:49 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philosopher	*init_philo(t_config *config, t_philosopher **philos, int num)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->data = init_data(num, config, philos);
	if (!philosopher->data)
	{
		free(philosopher);
		return (NULL);
	}
	return (philosopher);
}

int	is_anyone_dead(t_data *data)
{
	pthread_mutex_lock(&data->check_is_alive);
	if (data->is_alive == 0)
	{
		pthread_mutex_unlock(&data->check_is_alive);
		return (1);
	}
	pthread_mutex_unlock(&data->check_is_alive);
	return (0);
}

void	*philo_life(void *arg)
{
	t_data	*data;
	int		is_alive;
	int		num_fork;

	data = (t_data *) arg;
	if (data->num == 0)
		num_fork = data->config->nb_of_philo - 1;
	else
		num_fork = data->num - 1;
	is_alive = 1;
	while (is_alive)
	{
		if (!think_action(data, num_fork))
			return (NULL);
		if (!eat_action(data, num_fork))
			return (NULL);
		if (!sleep_action(data))
			return (NULL);
	}
	return (NULL);
}

void	free_philo(t_philosopher *philo)
{
	free_data(philo->data);
	free(philo);
}

void	free_philo_set(t_philosopher **philos, int i)
{
	while (i >= 0)
	{
		free_philo(philos[i]);
		--i;
	}
	free(philos);
}
