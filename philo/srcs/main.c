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

int	get_mls_time()
{

}

void	*run_philo(void *arg)
{
	t_data *data_philo;
	struct timeval present_time;

	data_philo = (t_data *) arg;
	if (gettimeofday(&present_time, NULL) == -1)
	{
		printf("Impossible d'obtenir le temps actuel !\n");
		return (NULL);
	}
	
	//pense
	printf(" %ld is thinking\n", num);
	pthread_mutex_lock(data_philo->right_fork);
	pthread_mutex_lock(data_philo->left_fork);

	//manger
	while (present_time < )


	return (NULL);
}

t_data *init_data(int num_thread, int nb_of_philo, t_philosopher **philos)
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
	if (num_thread > 1)
	{
		int position;
		if (num_thread != nb_of_philo - 1)
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

t_philosopher *init_philo(int num_thread, int nb_of_philo, t_philosopher **philos)
{
	t_philosopher *philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->data_philo = init_data(num_thread, nb_of_philo, philos);
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
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_eat;
	size_t i;
	t_philosopher **philos;

	if (argc < 4 && argc > 7)
	{
		printf("Mauvais nombre d argument\n");
		return (1);
	}
	//verif a faire sur les entres
	nb_of_philo = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		nb_of_eat = ft_atoi(argv[6]);
	philos = malloc(sizeof(t_philosopher *) * nb_of_philo);
	if (!philos)
		return (2);
	i = 0;
	while (i < nb_of_philo)
	{
		philos[i] = init_philo(i, nb_of_philo, philos);
		if (!philos[i])
		{
			//free les philos
			free(philos);
			return (3);
		}
		++i;
	}
	i = 0;
	while (i < nb_of_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		++i;
	}
	return (0);
}
