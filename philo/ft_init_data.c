/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:32:22 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/16 04:23:52 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_forks(pthread_mutex_t **array_forks, int n);
static int	ft_init_philos(t_philo **philos, pthread_mutex_t *array_forks, \
		int num_philos);
static int	ft_philos_allocation(t_philo **philos, int num_philos);

int	ft_init_data(int argc, char **argv, struct timeval tv, t_data *data)
{
	data->philos_n = ft_atoi(argv[1]);
	data->start_ts = tv.tv_sec * 1000000 + tv.tv_usec;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->meals = -1;
	if (6 == argc)
		data->meals = ft_atoi(argv[5]);
	data->deadth_flag = 0;
	data->array_philos = NULL;
	data->array_forks = NULL;
	if (EXIT_FAILURE == ft_init_forks(&(data->array_forks), data->philos_n))
		return (EXIT_FAILURE);
	if (EXIT_FAILURE == ft_init_philos(&(data->array_philos), \
				data->array_forks, data->philos_n))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Intialize forks mutex to bring lock and unlock shared resources */
static int	ft_init_forks(pthread_mutex_t **array_forks, int n)
{
	int	i;

	i = 0;
	*array_forks = (pthread_mutex_t *)malloc(n * sizeof(pthread_mutex_t));
	if (NULL == *array_forks)
		return (EXIT_FAILURE);
	while (i < 0)
	{
		if (0 != pthread_mutex_init(*(array_forks + i), NULL))
			return (free(*array_forks), array_forks = NULL, EXIT_FAILURE);
		i ++;
	}
	return (EXIT_SUCCESS);
}

/** Load data into philos structs. Things to have in consideration:
 *  - To have a clear order in the first take fork action, EVEN philos,
 *	ODD philo index, wait 1ms before start. In this way ODD philos always
 *	take his first fork first.
 *  - The order the philos take their forks to prevent deadlocks: 
 	EVEN first take left one, ODD the right one.
*/
static int	ft_init_philos(t_philo **philos, pthread_mutex_t *array_forks, \
		int num_philos)
{
	int	i;
	int	last_fork;

	i = 0;
	if (num_philos < 1)
		return (ft_putendl_fd("-philo: Minimun 1 philo", STDERR_FILENO), 1);
	if (EXIT_FAILURE == ft_philos_allocation(philos, num_philos))
		return (EXIT_FAILURE);
	while (i < num_philos)
	{
		(*(philos) + i)->philo_id = i + 1;
		(*(philos) + i)->start_eat = 0;
		(*(philos) + i)->start_sleep = 0;
		(*(philos) + i)->initial_delay = i % 2;
		(*(philos) + i)->first_fork = \
			&(array_forks[(i + (i % 2)) % num_philos]);
		last_fork = i + 1;
		if (i % (num_philos - 1) == 0 && i != 0)
			last_fork = i * (i % 2);
		else if (i % 2 != 0)
			last_fork --;
		(*(philos) + i)->second_fork = &(array_forks[last_fork]);
		i ++;
	}
	return (EXIT_SUCCESS);
}

/** Allocate dynamic memory for philos data */
static int	ft_philos_allocation(t_philo **philos, int num_philos)
{
	*philos = (t_philo *)malloc(sizeof(t_philo) * num_philos);
	if (NULL == *philos)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
