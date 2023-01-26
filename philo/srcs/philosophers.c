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

void    think()
{
    start_life = get_mls_time() - base_timer;
	printf("%ld %ld is thinking\n", start_life, data_philo->num);
	pthread_mutex_lock(&data_philo->right_fork);
	timer = get_mls_time() - base_timer;
	printf("%ld %ld has taken right fork\n", timer, data_philo->num);
	timer = get_mls_time() - base_timer;
	printf("%ld %ld has taken left fork\n", timer, data_philo->num);
	pthread_mutex_lock(&data_philo->left_fork);
	timer = get_mls_time() - base_timer;
	if ( timer > start_life + data_philo->config.time_to_die)
		is_alive = 0;
}

int   eat(t_data *data_philo, long base_timer, long *start_life, int *is_alive)
{
    long timer;
    long time_to_eat;

	*start_life = get_mls_time() - base_timer;
	timer = *start_life;
	printf("%ld %ld is eating\n", timer, data_philo->num);
	time_to_eat = timer + data_philo->config.time_to_eat;
	while (timer < time_to_eat)
    {
		usleep(5000);
        timer += 5;
        if (!is_not_dead(data_philo, timer, *start_life))
            return (0);
    }
    pthread_mutex_unlock(&data_philo->right_fork);
	pthread_mutex_unlock(&data_philo->left_fork);
	//is_not_dead(data_philo, timer, *start_life)
}

int    sleep(t_data *data_philo, long base_timer, long start_life)
{
    long    timer;
    long    
	timer = get_mls_time() - base_timer;
	printf("%ld %ld is sleeping\n", timer, data_philo->num);
	
    
    
    if (usleep(data_philo->config.time_to_sleep * 1000) == -1)
	{
		printf("impossible de dormir\n");
		return (0);
	}





	timer = get_mls_time() - base_timer;
	if ( timer > start_life + data_philo->config.time_to_die)
		is_alive = 0;

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
	while (is_alive)
	{
		//penser
        //manger
        //dormir
	}
	printf("%ld %ld died\n", timer, data_philo->num);
	return (NULL);
}