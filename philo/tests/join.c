#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void ft_printf(char c, void *arg)
{
	pthread_mutex_lock((pthread_mutex_t *)arg);
	printf("%c\n", c);
	pthread_mutex_unlock((pthread_mutex_t *)arg);
}

void	*routine(void *arg)
{
	int i = 0;
	while (i < 20)
	{
	ft_printf('1', arg);
	sleep(1);
	i ++;
	}
	return (arg);
}

void	*routine2(void *arg)
{
	while (1)
	{
	ft_printf('2', arg);
	sleep (2);
	}
	return (arg);
}

int main (void)
{
	pthread_t	thread;
	pthread_t	thread2;
	pthread_mutex_t mutex;

	if (pthread_create(&thread, NULL, &routine, &mutex) != 0)
	printf("ERROR\n");
	if (pthread_create(&thread2, NULL, &routine2, &mutex) != 0)
	printf("ERROR\n");
	if (pthread_mutex_init(&mutex, NULL) != 0)
	printf("ERROR\n");
	if (pthread_mutex_destroy(&mutex) != 0)
	printf("ERROR\n");
	pthread_join(thread, NULL);
	pthread_join(thread2, NULL);
	printf("___IMPRESION_PADRE\n");
	return (0);
}
