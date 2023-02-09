/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:05:24 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/09 17:32:06 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include "config.h"
# include "philosophers.h"

typedef struct s_config	t_config;
typedef struct s_data	t_data;
typedef struct s_philosopher	t_philosopher;
typedef struct s_data
{
	t_philosopher	**philos;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	acces_life_timer;
	t_config		*config;
	long			start_life;
	size_t			num;
	long			nb_eat;
}	t_data;

t_data	*init_data(int num_thread, t_config *config, t_philosopher **philos);
int		init_data_mutex(t_data *data);
void	free_data(t_data *data);
#endif
