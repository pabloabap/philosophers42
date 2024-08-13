//CABECERA

#include "philo.h"

int main(int argc, char **argv)
{
	int	status;
	struct timeval tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (EXIT_FAILURE);
	status = ft_input_check(argc, argv);
	ft_action_msg(1, tv.tv_usec, TAKE_FORK); 
	usleep(3);
	ft_action_msg(1, tv.tv_usec, EAT);
	usleep(3);
	ft_action_msg(1, tv.tv_usec, SLEEP); 
	usleep(3);
	ft_action_msg(1, tv.tv_usec, THINK); 
	usleep(3);
	ft_action_msg(1, tv.tv_usec, DIE); 
	usleep(3);
	return (status);
}
