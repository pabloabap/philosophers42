/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:28:45 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/16 04:18:38 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** Print error in STDERR_FILENO and return EXIT_FAILURE) */
int	ft_err_argn(void)
{
	ft_putstr_fd("-philo: Usage: './philo <n_of_philos> ", STDERR_FILENO);
	ft_putstr_fd("<time_to_die(ms)> <time_to_eat(ms)> ", STDERR_FILENO);
	ft_putstr_fd("<time_to_sleep(ms)> ", STDERR_FILENO);
	ft_putendl_fd("[times_each_philo_must_eat]'", STDERR_FILENO);
	return (EXIT_FAILURE);
}

/** Print error in STDERR_FILENO and return EXIT_FAILURE) */
int	ft_err_argv_format(void)
{
	ft_putendl_fd("-philo: Arguments must be unsigned digits.", STDERR_FILENO);
	return (EXIT_FAILURE);
}
