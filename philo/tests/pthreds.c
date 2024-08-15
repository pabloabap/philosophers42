#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	*routine(void *arg)
{
    sleep(*(int*)arg); 
    printf("IMPRESION DESDE EL HILO | PAUSA: %i\n", *(int*)arg);
    return (arg);
}

int main (void)
{
    pthread_t	thread;
    int		t_sleep = 2;

    if (pthread_create(&thread, NULL, &routine, &t_sleep) != 0)
	printf("ERROR\n");
    pthread_detach(thread);
//    pthread_join(thread, NULL);
    printf("___IMPRESION_PADRE\n");
    return (0);
}
