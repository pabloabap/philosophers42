/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:28:12 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/15 01:28:16 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat(t_philo *philo);
static int	ft_sleep(t_philo *philo);
static int	ft_think(t_philo *philo);

void	*ft_routine(void *arg)
{
	int		meals;
	t_philo	*philo;

	meals = 0;
	philo = (t_philo *)arg;
	while (philo->rules->end_flag != philo->rules->philos_n)
	{
		if (0 != ft_eat(philo) || 0 != ft_sleep(philo) || 0 != ft_think(philo))
			return ((void *)philo);
		if (++meals == philo->rules->mandatory_meals)
			ft_update_end_flag(philo->rules->end_flag_update, \
				&(philo->rules->end_flag), 0);
	}
	return ((void *)philo);
}

static int	ft_eat(t_philo *philo)
{
	struct timeval	tv;

	usleep(philo->initial_delay);
	philo->initial_delay = 0;
	if (0 != ft_take_forks(philo))
		return (ft_leave_fork(philo), EXIT_FAILURE);
	if (gettimeofday(&tv, NULL) < 0)
		return (ft_putendl_fd("-philo: Failure gettimeofday", 2), 1);
	if (philo->rules->philos_n > 1)
	{
		if (philo->rules->end_flag == philo->rules->philos_n)
			return (ft_leave_fork(philo), EXIT_FAILURE);
		philo->start_eat = \
			(tv.tv_sec * 1000000 + tv.tv_usec) - philo->rules->start_ts;
		ft_write_msg(philo->rules->write, "is eating", \
			philo->start_eat / 1000, philo->philo_id);
		usleep(philo->rules->time_eat);
	}
	else
		return (usleep(philo->rules->time_die), EXIT_FAILURE);
	if (0 != ft_leave_fork(philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_sleep(t_philo *philo)
{
	struct timeval	tv;

	if (philo->rules->end_flag == philo->rules->philos_n)
		return (EXIT_FAILURE);
	if (gettimeofday(&tv, NULL) < 0)
		return (ft_putendl_fd("-philo: Failure gettimeofday", 2), 1);
	philo->start_sleep = \
		(tv.tv_sec * 1000000 + tv.tv_usec) - philo->rules->start_ts;
	ft_write_msg(philo->rules->write, "is sleeping", \
		philo->start_sleep / 1000, philo->philo_id);
	usleep(philo->rules->time_sleep);
	return (EXIT_SUCCESS);
}

static int	ft_think(t_philo *philo)
{
	struct timeval	tv;
	long long		start_think;

	if (philo->rules->end_flag == philo->rules->philos_n)
		return (EXIT_FAILURE);
	if (gettimeofday(&tv, NULL) < 0)
		return (ft_putendl_fd("-philo: Failure gettimeofday", 2), 1);
	start_think = (tv.tv_sec * 1000000 + tv.tv_usec) - philo->rules->start_ts;
	ft_write_msg(philo->rules->write, "is thinking", start_think / 1000, \
		philo->philo_id);
	return (EXIT_SUCCESS);
}
