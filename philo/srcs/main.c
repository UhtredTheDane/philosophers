/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:11:01 by agengemb          #+#    #+#             */
/*   Updated: 2023/01/30 23:33:36 by agengemb         ###   ########.fr       */
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
		printf("Mauvais nombre d argument\n");
		return (1);
	}
	//verif a faire sur les entres
	config.nb_of_philo = ft_atoi(argv[1]);
	config.time_to_die = ft_atoi(argv[2]);
	config.time_to_eat = ft_atoi(argv[3]);
	config.time_to_sleep = ft_atoi(argv[4]);
	config.anyone_died = malloc(sizeof(int));
	if (!config.anyone_died)
		return (1);
	*config.anyone_died = 1;

	philos = malloc(sizeof(t_philosopher *) * config.nb_of_philo);
	if (!philos)
		return (2);
	i = 0;
	config.base_time = get_mls_time();
	while (i < config.nb_of_philo)
	{
		philos[i] = init_philo(i, &config, philos);
		if (!philos[i])
		{
			//free les philos
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
			free(philosopher);
			printf("Erreur creation thread %ld", philosopher->data_philo->num);
			return (NULL);
		}
	}
	i = 0;
	while (i < config.nb_of_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		++i;
	}
	return (0);
}
