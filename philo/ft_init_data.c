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

static int	ft_init_mutex(t_data *data);
static int	ft_init_forks(pthread_mutex_t **array_forks, int n);
static int	ft_init_philos(t_philo **philos, t_data *data);
static int	ft_philo_fill(t_philo **philos, int i, t_data *data);

int	ft_init_data(int argc, char **argv, struct timeval tv, t_data *data)
{
	data->philos_n = ft_atoi(argv[1]);
	if (data->philos_n < 1)
		return (ft_putendl_fd("-philo: Minimun 1 philo", STDERR_FILENO), 1);
	data->start_ts = tv.tv_sec * 1000000 + tv.tv_usec;
	data->time_die = ft_atoi(argv[2]) * 1000;
	data->time_eat = ft_atoi(argv[3]) * 1000;
	data->time_sleep = ft_atoi(argv[4]) * 1000;
	data->mandatory_meals = -1;
	if (6 == argc)
		data->mandatory_meals = ft_atoi(argv[5]);
	data->end_flag = 0;
	if (EXIT_FAILURE == ft_init_mutex(data))
		return (EXIT_FAILURE);
	if (EXIT_FAILURE == ft_init_philos(&(data->array_philos), data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_init_mutex(t_data *data)
{
	data->write = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->end_flag_update = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (NULL == data->write || NULL == data->end_flag_update)
		return (EXIT_FAILURE);
	if (0 != pthread_mutex_init(data->write, NULL) || \
		0 != pthread_mutex_init(data->end_flag_update, NULL) || \
		ft_init_forks(&(data->array_forks), data->philos_n))
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
	while (i < n)
	{
		if (0 != pthread_mutex_init((*(array_forks) + i), NULL))
			return (free(*array_forks), array_forks = NULL, EXIT_FAILURE);
		i ++;
	}
	return (EXIT_SUCCESS);
}

/** Load data into philos structs. Things to have in consideration:
 *  - To have a clear order in the first taken fork action, EVEN philos,
 *	ODD philo index, wait 1ms before start. In this way ODD philos always
 *	take their first fork first.
 *  - The order the philos take their forks to prevent deadlocks: 
 	EVEN first take left one, ODD the right one.
*/
static int	ft_init_philos(t_philo **philos, t_data *data)
{
	int	i;

	i = 0;
	if (EXIT_FAILURE == ft_philos_allocation(philos, data->philos_n))
		return (EXIT_FAILURE);
	while (i < data->philos_n)
		ft_philo_fill(philos, i ++, data);
	return (EXIT_SUCCESS);
}

static int	ft_philo_fill(t_philo **philos, int i, t_data *data)
{
	int	last_fork;

	(*(philos) + i)->philo_id = i + 1;
	(*(philos) + i)->start_eat = 0;
	(*(philos) + i)->start_sleep = 0;
	(*(philos) + i)->initial_delay = i % 2 * 500;
	(*(philos) + i)->first_fork = \
		&(data->array_forks[(i + (i % 2)) % data->philos_n]);
	last_fork = i + 1;
	if (i != 0 && i % (data->philos_n - 1) == 0)
		last_fork = i * (i % 2);
	else if (i % 2 != 0)
		last_fork --;
	(*(philos) + i)->second_fork = &(data->array_forks[last_fork]);
	(*(philos) + i)->thread_id = (pthread_t *)malloc(sizeof(pthread_t));
	(*(philos) + i)->rules = data;
	return (EXIT_SUCCESS);
}
