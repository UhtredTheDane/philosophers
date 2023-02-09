#include "../includes/philosophers.h"

int init_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->right_fork, NULL) != 0)
	{
			printf("Error init mutex %ld\n", data->num);
			free(data);
			return (0);
	}
	if (pthread_mutex_init(&data->acces_life_timer, NULL) != 0)
	{
			pthread_mutex_destroy(&data->right_fork);
			free(data);
			printf("Error init mutex %ld\n", data->num);
			return (0);
	}
	return (1);
}

t_data *init_data(int num_thread, t_config *config, t_philosopher **philos)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num = num_thread;
	data->start_life = 0;
	data->nb_eat = 0;
	data->philos = philos;
	data->config = config;
	if (!init_data_mutex(data))
	{
		free(data);
		return (NULL);
	}
	return (data);
}

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->right_fork);
	pthread_mutex_destroy(&data->acces_life_timer);
	free(data);
}
