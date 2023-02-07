#include "../includes/philosophers.h"

t_data *init_data(int num_thread, t_config *config, t_philosopher **philos)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num = num_thread;
	if (pthread_mutex_init(&data->right_fork, NULL) != 0)
	{
			printf("Error init mutex %d\n", num_thread);
			free(data);
			return (NULL);
	}
	if (pthread_mutex_init(&data->acces_life_timer, NULL) != 0)
	{
			pthread_mutex_destroy(&data->right_fork);
			free(data);
			printf("Error init mutex %d\n", num_thread);
			return (NULL);
	}
	data->start_life = 0;
	data->philos = philos;
	data->config = config;	
	return (data);
}

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->right_fork);
	pthread_mutex_destroy(&data->acces_life_timer);
	free(data);
}
