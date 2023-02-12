/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:59:16 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/12 20:43:54 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REAPER_H
# define REAPER_H

# include <pthread.h>
# include <unistd.h>
# include "data.h"
# include "philosophers.h"
# include "main.h"

typedef struct s_philosopher	t_philosopher;
typedef struct s_data			t_data;

void	*reaper_life(void *arg);
int		is_satisfied(t_data *data);
int		is_all_satisfied(t_data *data, int all_satisfied);
int		is_not_dead(t_data *data, long timer);
int		check_death(t_philosopher **philos, int all_satisfied);
#endif
