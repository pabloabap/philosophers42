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
	//ft_destroy_data - Funcion para acabar el programa limpio
	// LIBERACION DE MEMORIA DINAMICA - t_data->array_forks && array_philos;
	return (0);
}
