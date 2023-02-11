/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:03:30 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/09 17:25:20 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include "main.h"

typedef struct s_config
{
	pthread_mutex_t	acces_printer;
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_to_eat;
	struct timeval	base_time;
}			t_config;

int		init_config_mutex(t_config *config);
int		init_config(t_config *config, int nb_params, char **params);
void	destroy_mutex_config(t_config *config);
void	free_config(t_config *config);	
#endif
