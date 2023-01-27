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

int is_not_dead(t_data *data_philo, long timer, long start_life)
{
    if ( timer > start_life + data_philo->config.time_to_die)
	    return (0);
    return (1);
}

int    think(t_data *data_philo, long base_timer, long start_life)
{
	long timer;

	if (start_life == base_timer)
		timer = 0;
	else
		timer = get_mls_time() - base_timer;
	printf("%ld %ld is thinking\n", timer, data_philo->num);
	pthread_mutex_lock(&data_philo->right_fork);
	timer = get_mls_time() - base_timer;
	if (!is_not_dead(data_philo, timer, *start_life))
        return (0);
	printf("%ld %ld has taken right fork\n", timer, data_philo->num);
	pthread_mutex_lock(&data_philo->left_fork);
	timer = get_mls_time() - base_timer;
	if (!is_not_dead(data_philo, timer, *start_life))
        return (0);
	printf("%ld %ld has taken left fork\n", timer, data_philo->num);
	return (1);
}

int   eat(t_data *data_philo, long base_timer, long *start_life)
{
    long    res;
    long    rest;

	res = data_philo->config.time_to_eat / 5;
	rest = data_philo->config.time_to_eat % 5;
	*start_life = get_mls_time() - base_timer;
	printf("%ld %ld is eating\n", *start_life, data_philo->num);
	while (res >= 0)
	{
		if (res)
		{
			usleep(5 * 1000);
			if (!is_not_dead(data_philo, *start_life + 5, *start_life))
            	return (0);
		}
		else
		{
			usleep(rest * 1000);
			if (!is_not_dead(data_philo, *start_life + rest, *start_life))
            	return (0);
		}
		--res
	}
    pthread_mutex_unlock(&data_philo->right_fork);
	pthread_mutex_unlock(&data_philo->left_fork);
	return (1);
}

int    sleep(t_data *data_philo, long base_timer, long start_life)
{
    long    res;
    long    rest;

	res = data_philo->config.time_to_sleep / 5;
	rest = data_philo->config.time_to_sleep % 5;
	printf("%ld %ld is sleeping\n", get_mls_time() - base_timer, data_philo->num);
	while (res >= 0)
	{
		if (res)
		{
			usleep(5 * 1000);
			if (!is_not_dead(data_philo, *start_life + 5, *start_life))
            	return (0);
		}
		else
		{
			usleep(rest * 1000);
			if (!is_not_dead(data_philo, *start_life + rest, *start_life))
            	return (0);
		}
		--res
	}
	return (1);
}

void	*run_philo(void *arg)
{
	t_data *data_philo;
	long base_timer;
	long start_life;
	int is_alive;

	is_alive = 1;
	data_philo = (t_data *) arg;
	base_timer = get_mls_time();
	start_life = 0;
	while (is_alive)
	{
		if (think(data_philo, base_timer, start_life)
        //manger
        //dormir
	}
	printf("%ld %ld died\n", timer, data_philo->num);
	return (NULL);
}