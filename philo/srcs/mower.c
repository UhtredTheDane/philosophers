#include "../includes/philosophers.h"

void	*run_mower(void *arg)
{
    t_philosopher **philos;
    int alive;
    int i;
    int nb_of_philo;
    int timer;

    philos = (t_philosopher **) arg;
    alive = 1;
    nb_of_philo = philos[0]->data_philo->config->nb_of_philo;
    while (alive)
    { 
        usleep(2000);
	    i = 0;
        while (i < nb_of_philo)
        {
            timer = get_time_since(philos[i]->data_philo->config->base_time);
            if (!is_not_dead(philos[i]->data_philo, timer))
                return (NULL);
	    ++i;
        }
    }
    return (NULL);
}
