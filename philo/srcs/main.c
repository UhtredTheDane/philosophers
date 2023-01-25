/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:11:01 by agengemb          #+#    #+#             */
/*   Updated: 2023/01/22 21:38:51 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long convert_us_in_ms(suseconds_t *micro_nb)
{
	return (*micro_nb / 1000);
}

long convert_s_in_ms(time_t *s_nb)
{
	return (*s_nb / 0.001);
}

long	get_mls_time()
{
	struct timeval present_time;

	gettimeofday(&present_time, NULL);
	return (convert_s_in_ms(&(present_time.tv_sec)) + convert_us_in_ms(&(present_time.tv_usec)));
}

void	*run_philo(void *arg)
{
	t_data *data_philo;
	long timer;
	long base_timer;
	long start_life;
	long time_to_eat;
	int is_alive;

	is_alive = 1;
	data_philo = (t_data *) arg;
	base_timer = get_mls_time();
	while (is_alive)
	{
		//pense
		start_life = get_mls_time() - base_timer;
		printf("%ld %ld is thinking\n", start_life, data_philo->num);
		pthread_mutex_lock(&data_philo->right_fork);
		timer = get_mls_time() - base_timer;
		printf("%ld %ld has taken right fork\n", timer, data_philo->num);
		timer = get_mls_time() - base_timer;
		printf("%ld %ld has taken left fork\n", timer, data_philo->num);
		pthread_mutex_lock(&data_philo->left_fork);
		timer = get_mls_time() - base_timer;
		if ( timer > start_life + data_philo->config.time_to_die)
			is_alive = 0;
		
		if (is_alive)
		{
			//manger
			start_life = get_mls_time() - base_timer;
			timer = get_mls_time() - base_timer;
			printf("%ld %ld is eating\n", timer, data_philo->num);
			time_to_eat = timer + data_philo->config.time_to_eat;
			while ( timer < time_to_eat)
				timer = get_mls_time() - base_timer;
			pthread_mutex_unlock(&data_philo->right_fork);
			pthread_mutex_unlock(&data_philo->left_fork);
			if ( timer > start_life + data_philo->config.time_to_die)
				is_alive = 0;
		}
		if (is_alive)
		{
			//dormir
			timer = get_mls_time() - base_timer;
			printf("%ld %ld is sleeping\n", timer, data_philo->num);
			if (usleep(data_philo->config.time_to_sleep * 1000) == -1)
			{
				printf("impossible de dormir\n");
				return (NULL);
			}
			timer = get_mls_time() - base_timer;
			if ( timer > start_life + data_philo->config.time_to_die)
				is_alive = 0;
		}
	}
	printf("%ld %ld died\n", timer, data_philo->num);
	return (NULL);
}

t_data *init_data(int num_thread, t_config *config, t_philosopher **philos)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num = num_thread;
	if (pthread_mutex_init(&(data->right_fork), NULL) != 0)
	{
			printf("Error init mutex %d\n", num_thread);
			return (NULL);
	}
	data->config.nb_of_philo = config->nb_of_philo;
	data->config.time_to_die = config->time_to_die;
	data->config.time_to_eat = config->time_to_eat;
	data->config.time_to_sleep= config->time_to_sleep;

	if (num_thread > 1)
	{
		int position;
		if (num_thread != config->nb_of_philo - 1)
			position = num_thread - 1;
		else
		{
			position = 0;
			philos[position]->data_philo->left_fork = data->right_fork;
		}
		data->left_fork = philos[position]->data_philo->right_fork;
	}
	return (data);
}

/*
void	free_data(t_data *data)
{
	
	//pthread_mutex_destroy(pthread_mutex_t *mutex);
}*/

t_philosopher *init_philo(int num_thread, t_config *config, t_philosopher **philos)
{
	t_philosopher *philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->data_philo = init_data(num_thread, config, philos);
	if (!philosopher->data_philo)
	{
		free(philosopher);
		return (NULL);
	}
	if (pthread_create(&(philosopher->thread), NULL, run_philo, philosopher->data_philo) != 0)
	{
		//free_data();
		free(philosopher);
		printf("Erreur creation thread %ld", philosopher->data_philo->num);
		return (NULL);
	}
	return (philosopher);
}

int	main(int argc, char **argv)
{
	size_t i;
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
	


	philos = malloc(sizeof(t_philosopher *) * config.nb_of_philo);
	if (!philos)
		return (2);
	i = 0;
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
		pthread_join(philos[i]->thread, NULL);
		++i;
	}
	return (0);
}
