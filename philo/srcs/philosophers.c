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

int is_not_dead(t_data *data_philo, long timer)
{
	if (timer > data_philo->start_life + data_philo->config->time_to_die)
	{
		print_log(data_philo, timer, 0);
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
	int is_alive;
	int num_left_fork;

	data_philo = (t_data *) arg;
	num_left_fork = data_philo->num % data_philo->config->nb_of_philo - 1;
	if (num_left_fork == -1)
		num_left_fork = data_philo->config->nb_of_philo - 1;
	if (data_philo->num % 2)
		usleep(1000);
	is_alive = 1;
	while (is_alive)
		if (!think_action(data_philo, num_left_fork))
			is_alive = 0;

	return (NULL);
}
