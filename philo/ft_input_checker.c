/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:28:55 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/15 01:36:02 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** Check if the input is correct, otherwise return error message.
 * Input is correct when all arg characters are digits and the number 
 * of arguments are 4/5 (expluding program name). All args should be
 * grater that 1 except `number_of_times_ech_philosopher_must_eat`,
 * that is optional and can also be 0.
 * 
 * @param argc Number of arguments recibed by the program.
 * @param argv Values of the arguments.
 * 
*/

int	ft_input_check(int argc, char **argv)
{
	int i;
	int j;
	int	status;

	i = 1;
	j = 0;
	status = EXIT_SUCCESS;
	if (argc != 6 && argc != 7)
		status = ft_err_argn();
	while (argc > i && EXIT_SUCCESS == status)
	{
		while (argv[i][j] && EXIT_SUCCESS == status)
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				status = ft_err_argv_format();
			j++;
		}
		j = 0;
		i ++;
	}
	return (status);
}

/*
int	ft_args_to_int
{
	
}*/
