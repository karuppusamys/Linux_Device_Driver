#include<stdio.h>	//printf, scanf
#include<unistd.h>	//provides access to the POSIX operating system API
#include<pthread.h>
#include<semaphore.h>

int shared_var = 0;
sem_t sem_var;

void* thread_handler(void * arg)
{
	sem_wait(&sem_var);
	printf("going to access the common resources\n");
	shared_var++;
	sleep(5);
	printf("going to release the common resources\n");
	sem_post(&sem_var);
	
	return NULL;
}
int main(void)
{
	pthread_t thread_id[2];
	
	sem_init(&sem_var, 0, 1);
	
	pthread_create(&thread_id[0], NULL, thread_handler, NULL);
	pthread_create(&thread_id[1], NULL, thread_handler, NULL);
	
	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);
	sem_destroy(&sem_var);
	
	printf("Value of the shared variable: %d\n", shared_var);

	return 0;
}