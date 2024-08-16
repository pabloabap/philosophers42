/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:28:55 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/16 04:27:10 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_digits_check(int argc, char **argv);

/** Check if the input is correct, otherwise return error message.
 * 
 * @param argc Number of arguments recibed by the program.
 * @param argv Values of the arguments.
 * 
 * @return Exit status.
 * 
*/
int	ft_input_checks(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_err_argn());
	if (EXIT_FAILURE == ft_digits_check(argc, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/** Check that arguments are only digits */
static int	ft_digits_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argc > i)
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ft_err_argv_format());
			j++;
		}
		j = 0;
		i ++;
	}
	return (EXIT_SUCCESS);
}
