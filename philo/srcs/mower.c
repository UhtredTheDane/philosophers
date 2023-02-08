#include "../includes/philosophers.h"

int is_satisfied(t_data *data_philo)
{
    int res;

    pthread_mutex_lock(&data_philo->acces_life_timer);
    res = data_philo->config->nb_to_eat == data_philo->nb_eat;
    pthread_mutex_unlock(&data_philo->acces_life_timer);
    return (res);
}

int is_all_satisfied(t_data *data_philo, int all_satisfied)
{
    if (all_satisfied)
	{
		pthread_mutex_lock(&data_philo->config->check_if_dead);
		*data_philo->config->anyone_died = 0;
		pthread_mutex_unlock(&data_philo->config->check_if_dead);
		return (1);
	}
    return (0);
}

void	*run_mower(void *arg)
{
    t_philosopher **philos;
    int alive;
    int i;
    int nb_of_philo;
    int timer;
    int all_satisfied;

    philos = (t_philosopher **) arg;
    alive = 1;
    nb_of_philo = philos[0]->data_philo->config->nb_of_philo;
    while (alive)
    { 
        usleep(2000);
	    i = 0;
        all_satisfied = 1;
        while (i < nb_of_philo)
        {
            timer = get_time_since(philos[i]->data_philo->config->base_time);
            if (!is_not_dead(philos[i]->data_philo, timer))
                return (NULL);
            if (all_satisfied)
                all_satisfied = is_satisfied(philos[i]->data_philo);
        ++i;
        }
        if (is_all_satisfied(philos[0]->data_philo, all_satisfied))
            alive = 0;
    }
    return (NULL);
}
