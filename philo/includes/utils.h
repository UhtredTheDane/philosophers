/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:25:21 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/12 15:20:21 by agengemb         ###   ########.fr       */
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

#endif
