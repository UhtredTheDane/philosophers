
#include "../includes/philosophers.h"

int ft_sleep(long time_to_action)
{


    usleep(time_to_action * 1000);
    return (1);
}


int    think_action(t_data *data_philo, int num_left_fork)
{
	long timer;

	if (is_anyone_dead(data_philo))
		return (0);
    	timer = get_time_since(data_philo->config->base_time);
	if (!print_log(data_philo, timer, 1))
		return (0);
	pthread_mutex_lock(&data_philo->right_fork);
	if (is_anyone_dead(data_philo))
	{
		pthread_mutex_unlock(&data_philo->right_fork);
		return (0);
	}
	timer = get_time_since(data_philo->config->base_time);
	if(!print_log(data_philo, timer, 2))
	{
		pthread_mutex_unlock(&data_philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(&data_philo->philos[num_left_fork]->data_philo->right_fork);
	if (is_anyone_dead(data_philo))
	{
		drop_forks(data_philo, num_left_fork);
        return (0);
	}
	timer = get_time_since(data_philo->config->base_time);
	if (!print_log(data_philo, timer, 3))
	{
		drop_forks(data_philo, num_left_fork);
		return (0);
	}
	return (1);
}
 
int eat_action(t_data *data_philo, int num_left_fork)
{
	long timer;

	if (is_anyone_dead(data_philo))
    {
        drop_forks(data_philo, num_left_fork);
		return (0);
    }
	pthread_mutex_lock(&data_philo->acces_life_timer);
	data_philo->start_life = get_time_since(data_philo->config->base_time);
	timer = data_philo->start_life;
	pthread_mutex_unlock(&data_philo->acces_life_timer);
	if (!print_log(data_philo, timer, 4))
	{	
		drop_forks(data_philo, num_left_fork);
		return (0);
	}
    if (!ft_sleep(data_philo->config->time_to_eat))
	{
		drop_forks(data_philo, num_left_fork);
		return (0);
	}
	drop_forks(data_philo, num_left_fork);
	return (1);
}

int    sleep_action(t_data *data_philo)
{
	long timer;

	timer = get_time_since(data_philo->config->base_time);
	if (!print_log(data_philo, timer, 5))
		return (0);
	if (!ft_sleep(data_philo->config->time_to_sleep))
        return (0);
	return (1);
}
