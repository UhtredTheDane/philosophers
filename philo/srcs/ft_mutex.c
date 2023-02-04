#include "../includes/philosophers.h"

int drop_forks(t_data *data, int num, int with_return)
{
    pthread_mutex_unlock(&data->right_fork);
	pthread_mutex_unlock(&data->philos[num]->data_philo->right_fork);
}