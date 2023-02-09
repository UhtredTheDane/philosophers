#ifndef DATA_H
# define DATA_H

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
    long nb_eat;
    t_config *config;
    
} t_data;

int init_data_mutex(t_data *data);
t_data *init_data(int num_thread, t_config *config, t_philosopher **philos);
void	free_data(t_data *data);
#endif
