#include "../includes/philosophers.h"

t_philosopher *init_philo(t_config *config, t_philosopher **philos, int num_thread)
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
	return (philosopher);
}

int is_anyone_dead(t_data *data_philo)
{
	pthread_mutex_lock(&data_philo->config->check_if_dead);
	if (*data_philo->config->anyone_died == 0)
	{
		pthread_mutex_unlock(&data_philo->config->check_if_dead);
		return (1);
	}
	pthread_mutex_unlock(&data_philo->config->check_if_dead);
	return (0);
}

int is_not_dead(t_data *data_philo, long timer, long start_life)
{
    if (timer > start_life + data_philo->config->time_to_die)
	{
		printf("%ld %ld died\n", timer, data_philo->num);
		pthread_mutex_lock(&data_philo->config->check_if_dead);
		*data_philo->config->anyone_died = 0;
		pthread_mutex_unlock(&data_philo->config->check_if_dead);
	    return (0);
	}
    return (1);
}

void	*philo_life(void *arg)
{
	t_data *data_philo;
	long start_life;
	int is_alive;
	int num_left_fork;

	data_philo = (t_data *) arg;
	num_left_fork = data_philo->num % data_philo->config->nb_of_philo - 1;
	start_life = 0;
	is_alive = 1;
	while (is_alive)
		if (!think(data_philo, &start_life))
			return (NULL);

	return (NULL);
}
