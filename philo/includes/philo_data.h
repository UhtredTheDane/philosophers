#ifndef PHILO_DATA_H
# define PHILO_DATA_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
    size_t num;
    mutex_data right_fork;
    mutex_data left_fork;
} t_data;
#endif