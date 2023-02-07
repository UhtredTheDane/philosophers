#include "../includes/philosophers.h"

int init_config(t_config *config, char **params)
{
	//verif a faire sur les entres
	config->nb_of_philo = ft_atoi(params[0]);
	config->time_to_die = ft_atoi(params[1]);
	config->time_to_eat = ft_atoi(params[2]);
	config->time_to_sleep = ft_atoi(params[3]);
    if (pthread_mutex_init(&(config->check_if_dead), NULL) != 0)
	{
			printf("Error init mutex\n");
			return (0);
	}
	if (pthread_mutex_init(&(config->acces_printer), NULL) != 0)
	{
			printf("Error init mutex\n");
			return (0);
	}
	config->anyone_died = malloc(sizeof(int));
	if (!config->anyone_died)
		return (0);
	*config->anyone_died = 1;
	return (1);
}
