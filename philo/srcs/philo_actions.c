
#include "../includes/philosophers.h"

int ft_sleep(t_data *data_philo, long timer, long start_life)
{
    long    res;
    long    rest;

    res = data_philo->config->time_to_eat / 5;
	rest = data_philo->config->time_to_eat % 5;
    while (res >= 0)
	{
		if (res)
		{
			usleep(5 * 1000);
			timer += 5;
			if (is_anyone_dead(data_philo) || !is_not_dead(data_philo, timer, *start_life))
            	return (0);
		}
		else
		{
			usleep(rest * 1000);
			timer += rest;
			if (is_anyone_dead(data_philo) || !is_not_dead(data_philo, timer, *start_life))
				return (0);
		}
		--res;
	}
    return (1);
}


int    think_action(t_data *data_philo, long *start_life, int num_left_fork)
{
	long timer;

	if (is_anyone_dead(data_philo))
		return (0);
    timer = get_time_since(data_philo->config->base_time);
	printf("%ld ms %ld is thinking\n", timer, data_philo->num);
	pthread_mutex_lock(&data_philo->right_fork);
	if (is_anyone_dead(data_philo) || !is_not_dead(data_philo, timer, *start_life))
	{
        pthread_mutex_unlock(&data_philo->right_fork);
		return (0);
	}
	timer = get_time_since(data_philo->config->base_time);
	printf("%ld ms %ld has taken right fork\n", timer, data_philo->num);
	pthread_mutex_lock(&data_philo->philos[num_left_fork]->data_philo->right_fork);
	timer = get_time_since(data_philo->config->base_time);
	if (is_anyone_dead(data_philo) || !is_not_dead(data_philo, timer, *start_life))
	{
		drop_forks(data_philo, num_left_fork);
        return (0);
	}
	printf("%ld ms %ld has taken left fork\n", timer, data_philo->num);
	if (!eat(data_philo, start_life, num_left_fork))
			return (0);
	return (1);
}

int eat_action(t_data *data_philo, long *start_life, int num_left_fork)
{
	long timer;
    int sleep_return;

	*start_life = get_time_since(data_philo->config->base_time);
	if (is_anyone_dead(data_philo))
    {
        drop_forks(data_philo, num_left_fork);
		return (0);
    }
	timer = *start_life;
	printf("%ld ms %ld is eating\n", *start_life, data_philo->num);
    sleep_return = ft_sleep(data_philo, timer, *start_life);
    drop_forks(data_philo, num_left_fork);
    if (!sleep_return)
		return (0);
	if (!sleep_action(data_philo, *start_life))
		return (0);
	return (1);
}

int    sleep_action(t_data *data_philo, long start_life)
{
	long timer;

	if (is_anyone_dead(data_philo))
		return (0);
	timer = get_time_since(data_philo->config->base_time);
	printf("%ld %ld is sleeping\n", timer, data_philo->num);
	if (!ft_sleep(data_philo, timer, start_life))
        return (0);
	return (1);
}