/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 04:27:57 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/20 20:52:48 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &(s[i]), 1);
		i ++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

/** Allocate dynamic memory for philos data */
int	ft_philos_allocation(t_philo **philos, int num_philos)
{
	*philos = (t_philo *)malloc(sizeof(t_philo) * num_philos);
	if (NULL == *philos)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
