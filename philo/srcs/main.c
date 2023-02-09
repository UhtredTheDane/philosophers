/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:11:01 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/07 17:07:28 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philosopher	**prepare_philos(t_config *config)
{
	int			i;
	t_philosopher	**philos;

	philos = malloc(sizeof(t_philosopher *) * config->nb_of_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < config->nb_of_philo)
	{
		philos[i] = init_philo(config, philos, i);
		if (!philos[i])
		{
			/*while (i >= 0)
			{

				--i;
			}*/
			free_config(config);
			free(philos);
			return (NULL);
		}
		++i;
	}
	return (philos);
}

int run_philo(t_config *config, t_philosopher **philos)
{
	int i;

	i = 0;
	while (i < config->nb_of_philo)
	{
		if (pthread_create(&(philos[i]->thread), NULL, philo_life, philos[i]->data_philo) != 0)
		{
			//free_data();
			printf("Erreur creation thread %d", i);
			return (0);
		}
		++i;
	}
	return (1);
}

void wait_philo(t_config *config, t_philosopher **philos)
{
	int i;
	
	i = 0;
	while (i < config->nb_of_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		++i;
	}
}

int	main(int argc, char **argv)
{
	t_philosopher **philos;
	t_config config;
	pthread_t mower;
	
	if (argc < 5 && argc > 6)
	{
		printf("Usage: ./philo nb_philo time_to_die time_to_eat time_to_sleep [nb_times_philo_must_eat]\n");
		return (1); 
	}
	if (!init_config(&config, argc - 1, &argv[1]))
		return (2);
	philos = prepare_philos(&config);
	if (!philos)
		return (4);
	config.base_time = get_mls_time();
	if (!run_philo(&config, philos))
	{
		return (3);
	}
	if (pthread_create(&mower, NULL, run_mower, philos) != 0)
	{
		//free_data();
		printf("Erreur creation thread mower");
		return (0);
	}
	wait_philo(&config, philos);
	return (0);
}
