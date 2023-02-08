/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:03:43 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/08 16:58:33 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_config_mutex(t_config *config)
{
	if (pthread_mutex_init(&config->check_if_dead, NULL) != 0)
	{
		printf("Error init mutex\n");
		return (0);
	}
	if (pthread_mutex_init(&config->acces_printer, NULL) != 0)
	{
		pthread_mutex_destroy(&config->check_if_dead);
		printf("Error init mutex\n");
		return (0);
	}
	return (1);
}

//verif a faire sur les entres
int	init_config(t_config *config, int nb_params, char **params)
{
	config->nb_of_philo = ft_atoi(params[0]);
	config->time_to_die = ft_atoi(params[1]);
	config->time_to_eat = ft_atoi(params[2]);
	config->time_to_sleep = ft_atoi(params[3]);
	config->nb_to_eat = 0;
	if (nb_params == 5)
		config->nb_to_eat = ft_atoi(params[4]);
	if (!init_config_mutex(config))
		return (0);
	config->anyone_died = malloc(sizeof(int));
	if (!config->anyone_died)
		return (0);
	*config->anyone_died = 1;
	return (1);
}

void free_config(t_config *config)
{
	pthread_mutex_destroy(&config->check_if_dead);
	pthread_mutex_destroy(&config->acces_printer);
	free(config->anyone_died);
}
