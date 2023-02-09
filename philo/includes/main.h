/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:25:21 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/09 17:36:43 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include "philosophers.h"
# include "data.h"
# include "config.h"
# include "reaper.h"

typedef struct s_config	t_config;
typedef struct s_data	t_data;
typedef struct s_philosopher	t_philosopher;

t_philosopher	**prepare_philos(t_config *config);
void			wait_philo(t_config *config, t_philosopher **philos);
int				run_philo(t_config *config, t_philosopher **philos);
int				run_reaper(pthread_t *reaper, t_config *config, t_philosopher **philos);
int				print_log(t_data *data, long timer, int type);
int				ft_isdigit(int c);
int				ft_isspace(int c);
int				ft_atoi(const char *nptr);

#endif
