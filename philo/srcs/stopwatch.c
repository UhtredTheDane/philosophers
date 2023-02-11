/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopwatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:10:22 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/11 22:32:05 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stopwatch.h"

 
long	get_time_since(struct timeval *base_time)
{
	struct timeval	present_time;
	unsigned long s_nb;
	unsigned long micro_nb;

	gettimeofday(&present_time, NULL);
	s_nb = (present_time.tv_sec - base_time->tv_sec) * 1000000;
	micro_nb = present_time.tv_usec - base_time->tv_usec;
	return ((s_nb + micro_nb) / 1000);
}

