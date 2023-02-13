/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:25:21 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/13 20:03:39 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "data.h"

typedef struct s_data	t_data;

void	drop_forks(t_data *data, int num_fork);
void	print_death(t_data *data);
int		print_log(t_data *data, int type);
long	get_time_since(struct timeval *base_time);
void	unlock_good_fork(t_data *data, int num_fork, int res, int order);

#endif
