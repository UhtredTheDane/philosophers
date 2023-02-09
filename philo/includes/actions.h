#ifndef ACTIONS_H
# define ACTIONS_H

int    think_action(t_data *data_philo, int num_left_fork);
int eat_action(t_data *data_philo, int num_left_fork);
int    sleep_action(t_data *data_philo);

#endif