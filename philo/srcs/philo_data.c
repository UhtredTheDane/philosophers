#include "../includes/philosophers.h"

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
	if (pthread_mutex_init(&(data->check_if_dead), NULL) != 0)
	{
			printf("Error init mutex %d\n", num_thread);
			return (NULL);
	}
	data->philos = philos;
	data->config.nb_of_philo = config->nb_of_philo;
	data->config.time_to_die = config->time_to_die;
	data->config.time_to_eat = config->time_to_eat;
	data->config.time_to_sleep= config->time_to_sleep;
	data->config.anyone_died = config->anyone_died;
	data->config.base_time = config->base_time;	
	return (data);
}

/*
void	free_data(t_data *data)
{
	
	//pthread_mutex_destroy(pthread_mutex_t *mutex);
}*/
