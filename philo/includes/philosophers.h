/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:11:16 by agengemb          #+#    #+#             */
/*   Updated: 2023/01/22 21:11:18 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include "philo_data.h"
# include "config.h"
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
    pthread_t thread;
    t_data *data_philo;
}   t_philosopher;


int	ft_isdigit(int c);
static int	ft_isspace(int c);
int	ft_atoi(const char *nptr);
#endif