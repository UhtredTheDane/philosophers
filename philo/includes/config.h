/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:03:30 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/08 17:31:59 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include "utils.h"

typedef struct s_config
{
	pthread_mutex_t	acces_printer;
	pthread_mutex_t	check_if_dead;
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_to_eat;
	int				*anyone_died;
	long			base_time;
}			t_config;

int		init_config_mutex(t_config *config);
int		init_config(t_config *config, int nb_params, char **params);
void	free_config(t_config *config);	
#endif
