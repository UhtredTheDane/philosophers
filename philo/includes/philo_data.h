#ifndef PHILO_DATA_H
# define PHILO_DATA_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
    size_t num;
    pthread_mutex_t right_fork;
    pthread_mutex_t left_fork;
} t_data;
#endif