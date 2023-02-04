/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:11:01 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/04 10:08:27 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	int i;
	t_philosopher **philos;
	t_config config;
	
	if (argc < 4 && argc > 7)
	{
		printf("Error\n");
		return (1);
	}
	if (!init_config(&config, &argv[1]))
		return (2);
	
    	pthread_mutex_init(&(config.check_if_dead), NULL);
	philos = malloc(sizeof(t_philosopher *) * config.nb_of_philo);
	if (!philos)
		return (3);
	i = 0;
	while (i < config.nb_of_philo)
	{
		philos[i] = init_philo(&config, philos, i);
		if (!philos[i])
		{
			//free la config
			//free les deja fait philos
			free(philos);
			return (3);
		}
		++i;
	}
	i = 0;
	while (i < config.nb_of_philo)
	{
		if (pthread_create(&(philos[i]->thread), NULL, run_philo, philos[i]->data_philo) != 0)
		{
			//free_data();
			printf("Erreur creation thread %d", i);
			return (1);
		}
		++i;
	}
	i = 0;
	while (i < config.nb_of_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		++i;
	}
	return (0);
}
