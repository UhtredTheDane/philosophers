/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:11:01 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/13 16:51:48 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_philosopher	**prepare_philos(t_config *config)
{
	t_philosopher	**philos;
	int				i;

	philos = malloc(sizeof(t_philosopher *) * config->nb_of_philo);
	if (!philos)
	{
		free_config(config);
		return (NULL);
	}
	i = 0;
	while (i < config->nb_of_philo)
	{
		philos[i] = init_philo(config, philos, i);
		if (!philos[i])
		{
			free_philo_set(philos, i - 1);
			free_config(config);
			free(philos);
			return (NULL);
		}
		++i;
	}
	return (philos);
}

int	run_philo(t_config *config, t_philosopher **philos)
{
	int	i;

	gettimeofday(&config->base_time, NULL);
	i = 0;
	while (i < config->nb_of_philo)
	{
		if (pthread_create(&(philos[i]->thread),
				NULL, philo_life, philos[i]->data) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_lock(&philos[i]->data->check_is_alive);
				philos[i]->data->is_alive = 0;
				pthread_mutex_unlock(&philos[i]->data->check_is_alive);
			}
			printf("Erreur creation thread %d\n", i);
			free_philo_set(philos, config->nb_of_philo - 1);
			free_config(config);
			return (0);
		}
		++i;
	}
	return (1);
}

int	run_reaper(pthread_t *reaper, t_config *config, t_philosopher **philos)
{
	int	i;

	if (pthread_create(reaper, NULL, reaper_life, philos) != 0)
	{
		i = config->nb_of_philo;
		while (--i >= 0)
		{
			pthread_mutex_lock(&philos[i]->data->check_is_alive);
			philos[i]->data->is_alive = 0;
			pthread_mutex_unlock(&philos[i]->data->check_is_alive);
		}
		printf("Erreur creation thread reaper\n");
		free_philo_set(philos, config->nb_of_philo - 1);
		free_config(config);
		return (0);
	}
	return (1);
}

void	wait_philo(t_config *config, t_philosopher **philos)
{
	int	i;

	i = 0;
	while (i < config->nb_of_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		++i;
	}
}

int	main(int argc, char **argv)
{
	t_philosopher	**philos;
	t_config		config;
	pthread_t		reaper;

	if (argc < 5 || argc > 6)
	{
		printf("./philo nb_philo tm_die tm_eat tm_sleep [nb_tm_philo_eat]\n");
		return (1);
	}
	if (!init_config(&config, argc - 1, &argv[1]))
		return (2);
	philos = prepare_philos(&config);
	if (!philos)
		return (3);
	if (!run_philo(&config, philos))
		return (4);
	if (!run_reaper(&reaper, &config, philos))
		return (5);
	wait_philo(&config, philos);
	pthread_join(reaper, NULL);
	free_philo_set(philos, config.nb_of_philo - 1);
	free_config(&config);
	return (0);
}
