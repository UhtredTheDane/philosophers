/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:24:50 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/12 15:22:23 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "data.h"
# include "utils.h"

typedef struct s_data	t_data;

int    think_action(t_data *data, int num_fork);
int eat_action(t_data *data, int num_fork);
int    sleep_action(t_data *data);
void drop_forks(t_data *data, int num_fork);

#endif
