/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:11:16 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/04 12:20:03 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
  
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
   
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include "philo_data.h"
# include "config.h"
# include <sys/time.h>
# include <unistd.h>
 
typedef struct s_philosopher
{
    pthread_t thread;
    t_data *data_philo;
}   t_philosopher;


int	ft_isdigit(int c);
int	ft_isspace(int c);
int	ft_atoi(const char *nptr);
long	get_mls_time();
long convert_s_in_ms(time_t *s_nb);
long convert_us_in_ms(suseconds_t *micro_nb);
long get_time_since(long base_time);
t_philosopher *init_philo(t_config *config, t_philosopher **philos, int num_thread);
int is_anyone_dead(t_data *data_philo);
int is_not_dead(t_data *data_philo, long timer);
int    think_action(t_data *data_philo, int num_left_fork);
int eat_action(t_data *data_philo, int num_left_fork);
int    sleep_action(t_data *data_philo);
void	*philo_life(void *arg);
t_data *init_data(int num_thread, t_config *config, t_philosopher **philos);
int init_config(t_config *config, char **params);
t_philosopher	**prepare_philos(t_config *config);
int run_philo(t_config *config, t_philosopher **philos);
void wait_philo(t_config *config, t_philosopher **philos);
int ft_sleep(t_data *data_philo, long timer, long time_to_action);
void drop_forks(t_data *data, int num);
void	*run_mower(void *arg);
void print_log(t_data *data_philo, long timer, int type);
#endif
