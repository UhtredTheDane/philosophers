int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(const char *nptr)
{
	size_t	i;
	int		negatif;
	long	res;

	i = 0;
	negatif = 0;
	if (*(nptr + i) == '-')
	{
		++i;
		negatif = 1;
	}
	res = 0;
	while (*(nptr + i))
	{
		res += *(nptr + i) - '0';
		++i;
		if (*(nptr + i))
			res *= 10;
	}
	if (negatif)
		res *= -1;
	return (res);
}