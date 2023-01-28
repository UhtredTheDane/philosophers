 
#ifndef CONFIG_H
# define CONFIG_H

typedef struct s_config
{
    int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	long base_time;
	int *anyone_died;
    
} t_config;

#endif
