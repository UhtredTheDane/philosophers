#ifndef REAPER_H
# define REAPER_H

# include <pthread.h>
# include "philo_data.h"

int is_satisfied(t_data *data_philo);
int is_all_satisfied(t_data *data_philo, int all_satisfied);
int is_not_dead(t_data *data_philo, long timer);
int check_death(t_philosopher **philos, int all_satisfied);
void	*run_reaper(void *arg);
#endif