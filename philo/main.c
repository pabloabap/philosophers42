/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:27:45 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/16 04:39:11 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_run_fest(t_data *data);
static int	ft_supervisor(t_data *data);
static void	ft_die_logic(t_data *data, int current_ts, int i);

int	main(int argc, char **argv)
{
	struct timeval	tv;
	t_data			data;

	if (gettimeofday(&tv, NULL) < 0)
		return (ft_putendl_fd("-philo: Failure gettimeofday", 2), 1);
	if (EXIT_FAILURE == ft_input_checks(argc, argv))
		return (2);
	if (EXIT_FAILURE == ft_init_data(argc, argv, tv, &data))
		return (3);
	if (EXIT_FAILURE == ft_run_fest(&data))
		return (4);
	ft_clean_data(&data);
	return (0);
}

static int	ft_run_fest(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_n)
	{
		pthread_create(data->array_philos[i].thread_id, NULL, \
			&ft_routine, (void *)&(data->array_philos[i]));
		i ++;
	}
	ft_supervisor(data);
	i = 0;
	while (i < data->philos_n)
	{
		pthread_join(*(data->array_philos[i].thread_id), NULL);
		i ++;
	}
	return (EXIT_SUCCESS);
}

static int	ft_supervisor(t_data *data)
{
	int				i;
	struct timeval	tv;
	long long		current_ts;

	i = 0;
	while (data->end_flag < data->philos_n)
	{
		if (gettimeofday(&tv, NULL) < 0)
			return (ft_putendl_fd("-philo: Failure gettimeofday", 2), 1);
		current_ts = (tv.tv_sec * 1000000 + tv.tv_usec) - data->start_ts;
		while (i < data->philos_n)
			ft_die_logic(data, current_ts, i++);
		i = 0;
	}
	return (EXIT_SUCCESS);
}

static void	ft_die_logic(t_data *data, int current_ts, int i)
{
	if (data->array_philos[i].start_eat == 0)
	{
		if (current_ts > data->time_die)
		{
			ft_update_end_flag(data->end_flag_update, &data->end_flag, \
				data->philos_n);
			ft_write_msg(data->write, "died", current_ts / 1000, i + 1);
		}
	}
	else if ((current_ts - data->array_philos[i].start_eat) > data->time_die)
	{
		ft_write_msg(data->write, "died", current_ts / 1000, i + 1);
		ft_update_end_flag(data->end_flag_update, &data->end_flag, \
			data->philos_n);
	}
}
