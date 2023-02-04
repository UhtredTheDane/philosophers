#include "../includes/philosophers.h"

t_data *init_data(int num_thread, t_config *config, t_philosopher **philos, pthread_mutex_t check_if_dead)
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
	data->check_if_dead = check_if_dead;
	data->philos = philos;
	data->config = config;	
	return (data);
}

/*
void	free_data(t_data *data)
{
	
	//pthread_mutex_destroy(pthread_mutex_t *mutex);
}*/
