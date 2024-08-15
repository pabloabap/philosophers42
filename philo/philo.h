/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabad-ap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:28:26 by pabad-ap          #+#    #+#             */
/*   Updated: 2024/08/15 01:28:32 by pabad-ap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_create, detach, join, mutex_init, mutex_destroy, mutex_lock, mutex_unlock
#include <errno.h> //macro de errnos


int		ft_input_check(int argc, char **argv);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_action_msg(int philo_id, suseconds_t ms, int action);

//ERRORS
int	ft_err_argn(void);
int	ft_err_argv_format(void);

#endif
