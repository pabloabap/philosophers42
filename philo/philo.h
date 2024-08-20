/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:28:26 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/20 16:50:40 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

typedef struct s_philo
{
	int				philo_id;
	long long		start_eat;
	long long		start_sleep;
	int				initial_delay;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_t		*thread_id;
	struct s_data	*rules;
}					t_philo;

typedef struct s_data
{
	int				philos_n;
	long long		start_ts;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				mandatory_meals;
	int				end_flag;
	pthread_mutex_t	*array_forks;
	pthread_mutex_t	*write;
	pthread_mutex_t	*end_flag_update;
	t_philo			*array_philos;
}					t_data;		

//Utils
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);

//Program funcionts
int		ft_input_checks(int argc, char **argv);
int		ft_init_data(int argc, char **argv, struct timeval tv, t_data *data);

//ERRORS
int		ft_err_argn(void);
int		ft_err_argv_format(void);

void	ft_clean_data(t_data *data);
int		ft_update_end_flag(pthread_mutex_t *locker, int *end_flag, int deadth);
void	ft_write_msg(pthread_mutex_t *write_locker, char *msg, long long ts, \
	int philo_id);
void	*ft_routine(void *arg);

int		ft_take_forks(t_philo *philo);
int		ft_leave_fork(t_philo *philo);
int		ft_philos_allocation(t_philo **philos, int num_philos);

#endif
