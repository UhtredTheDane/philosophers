/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:11:16 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/12 20:47:37 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include "data.h"
# include "config.h"
# include "actions.h"
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config	t_config;
typedef struct s_data	t_data;

typedef struct s_philosopher
{
	pthread_t	thread;
	t_data		*data;
}	t_philosopher;

t_philosopher	*init_philo(t_config *config, t_philosopher **philos, int num);
int				is_anyone_dead(t_data *data);
void			*philo_life(void *arg);
void			free_philo(t_philosopher *philo);
void			free_philo_set(t_philosopher **philos, int i);
#endif
