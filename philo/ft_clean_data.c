// CABECERA

#include "philo.h"

void	ft_clean_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_n)
	{
		pthread_mutex_destroy(&(data->array_forks[i]));
		free(data->array_philos[i].thread_id);
		i ++;
	}
	pthread_mutex_destroy(data->end_flag_update);
	free(data->write);
	free(data->end_flag_update);
	free(data->array_forks);
	free(data->array_philos);
}
