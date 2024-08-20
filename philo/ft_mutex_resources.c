/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_resources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:33:37 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/20 16:33:43 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_update_end_flag(pthread_mutex_t *locker, int *end_flag, int deadth)
{
	if (0 != pthread_mutex_lock(locker))
		return (EXIT_FAILURE);
	if (deadth == 0)
		*end_flag += 1;
	else
		*end_flag = deadth;
	if (0 != pthread_mutex_unlock(locker))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_write_msg(pthread_mutex_t *write_locker, char *msg, long long ts, \
	int philo_id)
{
	pthread_mutex_lock(write_locker);
	printf("%lli %i %s\n", ts, philo_id, msg);
	pthread_mutex_unlock(write_locker);
}

int	ft_take_forks(t_philo *philo)
{
	struct timeval	tv;
	long long		timestamp;

	if (0 != pthread_mutex_lock(philo->first_fork))
		return (EXIT_FAILURE);
	if (gettimeofday(&tv, NULL) < 0)
		return (ft_putendl_fd("-philo: Failure gettimeofday", 2), 1);
	timestamp = (tv.tv_sec * 1000000 + tv.tv_usec) - philo->rules->start_ts;
	if (philo->rules->end_flag == philo->rules->philos_n)
		return (EXIT_FAILURE);
	ft_write_msg(philo->rules->write, "has taken a fork", timestamp / 1000, \
		philo->philo_id);
	if (philo->rules->philos_n == 1)
		return (EXIT_FAILURE);
	if (0 != pthread_mutex_lock(philo->second_fork))
		return (EXIT_FAILURE);
	if (gettimeofday(&tv, NULL) < 0)
		return (ft_putendl_fd("-philo: Failure gettimeofday", 2), 1);
	timestamp = (tv.tv_sec * 1000000 + tv.tv_usec) - philo->rules->start_ts;
	if (philo->rules->end_flag == philo->rules->philos_n)
		return (EXIT_FAILURE);
	ft_write_msg(philo->rules->write, "has taken a fork", timestamp / 1000, \
		philo->philo_id);
	return (EXIT_SUCCESS);
}

int	ft_leave_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		if (0 != pthread_mutex_unlock(philo->second_fork))
			return (EXIT_FAILURE);
		usleep (50);
		if (0 != pthread_mutex_unlock(philo->first_fork))
			return (EXIT_FAILURE);
	}
	else
	{
		if (0 != pthread_mutex_unlock(philo->first_fork))
			return (EXIT_FAILURE);
		if (philo->rules->philos_n > 1)
		{
			usleep (50);
			if (0 != pthread_mutex_unlock(philo->second_fork))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
