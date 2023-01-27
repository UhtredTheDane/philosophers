#ifndef PHILO_DATA_H
# define PHILO_DATA_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include "config.h"

typedef struct s_data
{
    size_t num;
    pthread_mutex_t right_fork;
    pthread_mutex_t left_fork;
    pthread_mutex_t check_if_dead;
    t_config config;
    
} t_data;
#endif