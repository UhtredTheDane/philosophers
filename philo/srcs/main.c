/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:11:01 by agengemb          #+#    #+#             */
/*   Updated: 2023/01/22 21:38:51 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*philo_job(void *arg)
{
	
}

int	main(int argc, char **argv)
{
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_eat;

	if (argc < 4 && argc > 7)
	{
		printf("Mauvais nombre d argument\n");
		return (1);
	}
	//verif a faire sur les entres
	nb_of_philo = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		nb_of_eat = ft_atoi(argv[6]);

	pthread_t *threads;
	threads = malloc(sizeof(pthread_t) * nb_of_philo);
	if (!thread)
		return (2);
	size_t	i;
	i = 0;
	while (i < nb_of_philo)
	{
		pthread_create(&threads[i], NULL, philo_job, data);
		++i;
	}
	i = 0;
	while (i < nb_of_philo)
	{
		pthread_join(threads[i], NULL);
		++i;
	}
	return (0);
}
