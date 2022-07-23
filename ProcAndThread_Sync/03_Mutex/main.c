#include<stdio.h>
#include<unistd.h>	//usleep, sleep
#include<pthread.h>

int sharedVar = 0;

pthread_mutex_t lock;


void* thread_handler2(void* arg)
{
	pthread_mutex_lock(&lock);
	printf("I am in starding of thread\n");
	sharedVar++;
	sleep(5);
	printf("I am in ending of thread\n");
	pthread_mutex_unlock(&lock);

	return NULL;
}

void* thread_handler1(void* arg)
{
	pthread_mutex_lock(&lock);
	printf("I am in starding of thread\n");
	sharedVar++;
	sleep(5);
	printf("I am in ending of thread\n");
	pthread_mutex_unlock(&lock);

	return NULL;
}

int main(void)
{
	pthread_t th_id[2];
	if(pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("Failed to init the mutex\n");
		return -1;
	}

	printf("I am from main\n");
	pthread_create(&th_id[0], NULL, thread_handler1, NULL);
//	sleep(1);
//	pthread_mutex_unlock(&lock);
	pthread_create(&th_id[1], NULL, thread_handler2, NULL);
	pthread_join(th_id[0], NULL);
	pthread_join(th_id[1], NULL);
	pthread_mutex_destroy(&lock);

	printf("Value of shared variable: %d\n", sharedVar);
	return 0;
}