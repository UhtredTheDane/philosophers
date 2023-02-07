#ifndef PHILO_DATA_H
# define PHILO_DATA_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include "config.h"
# include "philosophers.h"

typedef struct s_philosopher t_philosopher;
typedef struct s_data
{ 
    size_t num;
    t_philosopher **philos;
    pthread_mutex_t right_fork;
    pthread_mutex_t acces_life_timer;
    long start_life;
    t_config *config;
    
} t_data;
#endif
