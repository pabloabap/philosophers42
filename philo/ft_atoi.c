/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <pabad-ap@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:08:07 by pabad-ap          #+#    #+#             */
/*   Updated: 2023/09/30 00:17:31 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	sign;
	int	num;

	index = 0;
	sign = 1;
	num = 0;
	while ((str[index] >= '\t' && str[index] <= '\r') || str[index] == ' ')
		index ++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -1;
		index ++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		if (((num < 0) && ((num * 10 + ((str[index] - 48) * sign)) > num)) \
				|| ((num > 0) && ((num * 10 + (str[index] - 48)) < num)))
			return (0);
		num = num * 10 + ((str[index] - 48) * sign);
		index ++;
	}
	return (num);
}
