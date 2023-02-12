/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:03:43 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/09 17:04:33 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/config.h"

int	init_config_mutex(t_config *config)
{
	if (pthread_mutex_init(&config->acces_printer, NULL) != 0)
	{
		printf("Error init acces_printer mutex\n");
		return (0);
	}
	return (1);
}

int	init_config(t_config *config, int nb_params, char **params)
{
	config->nb_of_philo = ft_atol(params[0]);
	config->time_to_die = ft_atol(params[1]);
	config->time_to_eat = ft_atol(params[2]);
	config->time_to_sleep = ft_atol(params[3]);
	if (!config->nb_of_philo || !config->time_to_die
		|| !config->time_to_eat || !config->time_to_sleep)
	{
		printf("Erreur, parametres d'entrée non valides.\n");
		return (0);
	}
	config->nb_to_eat = 0;
	if (nb_params == 5)
		config->nb_to_eat = ft_atoi(params[4]);
	if (!init_config_mutex(config))
		return (0);
	return (1);
}

void	free_config(t_config *config)
{
	pthread_mutex_destroy(&config->acces_printer);
}
