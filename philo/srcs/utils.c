/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:11:26 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/09 17:11:45 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	print_log(t_data *data, long timer, int type)
{
	pthread_mutex_lock(&data->config->acces_printer);
	if (type == 0)
	{
		printf("%ld ms %ld died\n", timer, data->num);
		pthread_mutex_unlock(&data->config->acces_printer);
		return (1);
	}
	if (is_anyone_dead(data))
	{
		pthread_mutex_unlock(&data->config->acces_printer);
		return (0);
	}
	if (type == 1)
		printf("%ld ms %ld is thinking\n", timer, data->num);
	else if (type == 2)
		printf("%ld ms %ld has taken a fork\n", timer, data->num);
	else if (type == 3)
		printf("%ld ms %ld is eating\n", timer, data->num);
	else if (type == 4)
		printf("%ld ms %ld is sleeping\n", timer, data->num);
	pthread_mutex_unlock(&data->config->acces_printer);
	return (1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		negatif;
	int		res;

	i = 0;
	while (ft_isspace(*(nptr + i)))
		i++;
	negatif = 0;
	if (*(nptr + i) == '-' || *(nptr + i) == '+')
		if (*(nptr + i++) == '-')
			negatif = 1;
	res = 0;
	while (ft_isdigit(*(nptr + i)))
	{
		res += (*(nptr + i) - '0');
		i++;
		if (ft_isdigit(*(nptr + i)))
			res *= 10;
	}
	if (negatif)
		res *= -1;
	return (res);
}
