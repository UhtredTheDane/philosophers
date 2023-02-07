 
#ifndef CONFIG_H
# define CONFIG_H
 
typedef struct s_config
{
    int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int *anyone_died;
	long base_time;
	pthread_mutex_t check_if_dead;
	pthread_mutex_t acces_printer;
} t_config;

#endif
