/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:19:35 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/12 20:19:39 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_atol.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *nptr)
{
	size_t	i;
	long	res;

	i = 0;
	res = 0;
	while (*(nptr + i))
	{
		if (!ft_isdigit(*(nptr + i)))
			return (0);
		res += *(nptr + i) - '0';
		++i;
		if (*(nptr + i))
			res *= 10;
	}
	if (INT_MAX < res)
		return (0);
	return (res);
}
