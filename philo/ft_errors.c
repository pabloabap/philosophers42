// CABECERA

#include "philo.h"

/** Print error in STDERR_FILENO and return EXIT_FAILURE) */
int	ft_err_argn(void)
{
	ft_putstr_fd("-philo: Usage: './philo <n_of_philos> ", STDERR_FILENO);
	ft_putstr_fd("<time_to_die(ms)> <time_to_eat(ms)> ", STDERR_FILENO);
	ft_putstr_fd("<time_to_sleep(ms)> ", STDERR_FILENO);
	ft_putendl_fd("[times_each_philo_must_eat]'",STDERR_FILENO);
	return (EXIT_FAILURE);
}

/** Print error in STDERR_FILENO and return EXIT_FAILURE) */
int	ft_err_argv_format(void)
{
	ft_putendl_fd("-philo: Arguments must be digits.",STDERR_FILENO);
	return (EXIT_FAILURE);
}
