#include "../includes/philosophers.h"

t_philosopher *init_philo(int num_thread, t_config *config, t_philosopher **philos)
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
	if (pthread_create(&(philosopher->thread), NULL, run_philo, philosopher->data_philo) != 0)
	{
		//free_data();
		free(philosopher);
		printf("Erreur creation thread %ld", philosopher->data_philo->num);
		return (NULL);
	}
	return (philosopher);
}

int is_anyone_dead(t_data *data_philo)
{
	pthread_mutex_lock(&data_philo->check_if_dead);
	if (*data_philo->config.anyone_died == 0)
	{
		pthread_mutex_unlock(&data_philo->check_if_dead);
		return (1);
	}
	pthread_mutex_unlock(&data_philo->check_if_dead);
	return (0);
	
}

int is_not_dead(t_data *data_philo, long timer, long start_life)
{
    if (timer > start_life + data_philo->config.time_to_die)
	{
		printf("%ld %ld died\n", timer, data_philo->num);
		pthread_mutex_lock(&data_philo->check_if_dead);
		*data_philo->config.anyone_died = 0;
		pthread_mutex_unlock(&data_philo->check_if_dead);
	    return (0);
	}
    return (1);
}

int    think(t_data *data_philo, long base_time, long start_life)
{
	long timer;

	timer = get_mls_time() - base_time;
	if (is_anyone_dead(data_philo))
		return (0);
	printf("%ld %ld is thinking\n", timer, data_philo->num);
	pthread_mutex_lock(&data_philo->right_fork);
	timer = get_mls_time() - base_time;
	if (!is_not_dead(data_philo, timer, start_life) || is_anyone_dead(data_philo))
        	return (0);
	printf("%ld %ld has taken right fork\n", timer, data_philo->num);
	
	if (data_philo->num == 0)
		pthread_mutex_lock(&data_philo->philos[data_philo->config.nb_of_philo - 1]->data_philo->right_fork);
	else
		pthread_mutex_lock(&data_philo->philos[data_philo->num - 1]->data_philo->right_fork);
	
	timer = get_mls_time() - base_time;
	if (!is_not_dead(data_philo, timer, start_life) || is_anyone_dead(data_philo))
        	return (0);
	printf("%ld %ld has taken left fork\n", timer, data_philo->num);
	if (!eat(data_philo, data_philo->config.base_time, &start_life))
			return (0);
	return (1);
}

int eat(t_data *data_philo, long base_time, long *start_life)
{
    long    res;
    long    rest;
	long timer;

	res = data_philo->config.time_to_eat / 5;
	rest = data_philo->config.time_to_eat % 5;
	*start_life = get_mls_time() - base_time;
	if (is_anyone_dead(data_philo))
		return (0);
	timer = *start_life;
	printf("%ld %ld is eating\n", *start_life, data_philo->num);
	while (res >= 0)
	{
		printf("%ld entrain de manger\n", data_philo->num);
		if (res)
		{
			usleep(5 * 1000);
			timer += 5;
			if (!is_not_dead(data_philo, timer, *start_life) || is_anyone_dead(data_philo))
            	return (0);
		}
		else
		{
			usleep(rest * 1000);
			timer += rest;
			if (!is_not_dead(data_philo, timer, *start_life) || is_anyone_dead(data_philo))
            	return (0);
		}
		--res;
	}
    pthread_mutex_unlock(&data_philo->right_fork);
	if (data_philo->num == 0)
		pthread_mutex_unlock(&data_philo->philos[data_philo->config.nb_of_philo - 1]->data_philo->right_fork);
	else
		pthread_mutex_unlock(&data_philo->philos[data_philo->num - 1]->data_philo->right_fork);
	if (!sleep_action(data_philo, data_philo->config.base_time, *start_life))
			return (0);
	return (1);
}

int    sleep_action(t_data *data_philo, long base_time, long start_life)
{
    long    res;
    long    rest;
	long timer;

	res = data_philo->config.time_to_sleep / 5;
	rest = data_philo->config.time_to_sleep % 5;
	if (is_anyone_dead(data_philo))
		return (0);
	timer = get_mls_time() - base_time;
	printf("%ld %ld is sleeping\n", timer, data_philo->num);
	while (res >= 0)
	{
		if (res)
		{
			usleep(5 * 1000);
			timer += 5;
			if (!is_not_dead(data_philo, timer, start_life) || is_anyone_dead(data_philo))
            			return (0);
		}
		else
		{
			usleep(rest * 1000);
			timer += rest;
			if (!is_not_dead(data_philo, timer, start_life) || is_anyone_dead(data_philo))
            			return (0);
		}
		--res;
	}
	return (1);
}

void	*run_philo(void *arg)
{
	t_data *data_philo;
	long start_life;
	int is_alive;

	data_philo = (t_data *) arg;
	start_life = 0;
	is_alive = 1;
	while (is_alive)
		if (!think(data_philo, data_philo->config.base_time, start_life))
			return (NULL);

	return (NULL);
}
