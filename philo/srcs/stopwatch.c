/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopwatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:10:22 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/09 17:11:06 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stopwatch.h"

long	convert_us_in_ms(suseconds_t *micro_nb)
{
	return (*micro_nb / 1000);
}

long	convert_s_in_ms(time_t *s_nb)
{
	return (*s_nb / 0.001);
}

long	get_mls_time(void)
{
	struct timeval	present_time;

	gettimeofday(&present_time, NULL);
	return (convert_s_in_ms(&(present_time.tv_sec))
		+ convert_us_in_ms(&(present_time.tv_usec)));
}

long	get_time_since(long base_time)
{
	return (get_mls_time() - base_time);
}
