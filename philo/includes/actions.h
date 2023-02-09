/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:24:50 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/09 17:32:48 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "data.h"
# include "stopwatch.h"

typedef struct s_data	t_data;

int    think_action(t_data *data, int num_left_fork);
int eat_action(t_data *data, int num_left_fork);
int    sleep_action(t_data *data);
void drop_forks(t_data *data, int num);

#endif
