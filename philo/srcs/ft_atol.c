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
			return (-1);
		res += *(nptr + i) - '0';
		++i;
		if (*(nptr + i))
			res *= 10;
	}
	return (res);
}