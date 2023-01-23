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


/* 
 * Description:
 * 
 * Converts the initial portion of the string pointed to nptr 
 * to int representation.
 */

static int	ft_isspace(int c)
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
void	*run_philo(void *arg)
{
	
	return (NULL);
}

t_data *init_data(int num_thread, t_philosopher *philos)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num = num_thread;
	if (pthread_mutex_init(&(data->right_fork.mutex), NULL) != 0)
	{
			printf("Error init mutex %d\n", i);
			return (NULL);
	}
	if (num_thread > 1)
	{
		int position;
		if (num_thread != nb_of_philo - 1)
			position = num_thread - 1;
		else
		{
			position = 0;
			philos[position].data_philo.left_fork = data->right_fork.mutex;
		}
		data->left_fork = philos[position].data_philo.right_fork;
		philos[position].data_philo.left_fork = 
	}
	return (data);
}

t_philosopher *init_philo(int i)
{
	t_philosopher *philosophers;

	philosophers = malloc(sizeof(t_philosopher));
	if (!philosophers)
		return (NULL);
	philosophers->data_philo = init_data();
	if (!philosophers->data_philo)
	{
		free(philosophers);
		return (NULL);
	}

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

	t_data *data_philos;
	data_philo = malloc(sizeof(pthread_t) * nb_of_philo);
	if (!data_philo)
		return (2);
	mutex_data *forks;
	pthread_t *philosophers;
	philosophers = malloc(sizeof(pthread_t) * nb_of_philo);
	if (!philosophers)
	{
		free(data_philo);
		return (3);
	}
	forks = malloc(sizeof(mutex_data) * nb_of_philo);
	if (!forks)
	{
		free(data_philo);
		free(philosophers);
		return (4);
	}
	size_t	i;
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_mutex_init(&(forks[i].mutex), NULL)) == 0)
		{
			printf("Error init mutex %d\n", i);
			return (5);
		}
		data_philos[i].right_fork = da
		pthread_create(&philosophers[i], NULL, run_philo, data_philo[]);
		++i;
	}
	i = 0;
	while (i < nb_of_philo)
	{
		pthread_join(philosophers[i], NULL);
		++i;
	}
	return (0);
}
