#include "../includes/philosophers.h"

void drop_forks(t_data *data, int num)
{
    pthread_mutex_unlock(&data->right_fork);
	pthread_mutex_unlock(&data->philos[num]->data_philo->right_fork);
}