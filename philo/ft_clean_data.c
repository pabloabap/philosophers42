/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:33:22 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/20 16:33:28 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_n)
	{
		pthread_mutex_destroy(&(data->array_forks[i]));
		free(data->array_philos[i].thread_id);
		i ++;
	}
	pthread_mutex_destroy(data->end_flag_update);
	free(data->write);
	free(data->end_flag_update);
	free(data->array_forks);
	free(data->array_philos);
}
