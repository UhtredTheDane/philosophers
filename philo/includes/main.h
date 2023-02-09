#ifndef MAIN_H
# define MAIN_H

void wait_philo(t_config *config, t_philosopher **philos);
int run_philo(t_config *config, t_philosopher **philos);
t_philosopher	**prepare_philos(t_config *config);
int print_log(t_data *data_philo, long timer, int type);
int	ft_isdigit(int c);
int	ft_isspace(int c);
int	ft_atoi(const char *nptr);
#endif