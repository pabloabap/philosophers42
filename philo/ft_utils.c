/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 04:27:57 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/16 04:28:15 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

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

void	ft_putnbr_fd(int n, int fd)
{
	char	sign;

	sign = '+';
	if (n < 0)
	{
		sign = '-';
		ft_putchar_fd(sign, fd);
		if (n == -2147483648)
		{
			n = -147483648;
			ft_putchar_fd('2', fd);
		}
		n *= -1;
	}
	if (n / 10 == 0)
		n %= 10;
	else
	{
		ft_putnbr_fd(n / 10, fd);
		n = n % 10;
	}
	ft_putchar_fd((n % 10) + 48, fd);
}

/** Allocate dynamic memory for philos data */
int	ft_philos_allocation(t_philo **philos, int num_philos)
{
	*philos = (t_philo *)malloc(sizeof(t_philo) * num_philos);
	if (NULL == *philos)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
