/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:28:26 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/16 04:33:36 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_create|detach|join, mutex_init, destroy,[un]lock
# include <errno.h> //macro de errnos

typedef struct s_philo
{
	int				philo_id;
	long long		start_eat;
	long long		start_sleep;
	int				initial_delay;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
}					t_philo;

typedef struct s_data
{
	int				philos_n;
	long long		start_ts;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meals;
	int				deadth_flag;
	pthread_mutex_t	*array_forks;
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

#endif
