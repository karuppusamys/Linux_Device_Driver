#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_t tid1, tid2;
int thread1_result;

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* my_thread(void *arg)
{
	printf("%s: I am going to wait for acquire a lock\n", arg);
	pthread_mutex_lock(&lock);
	printf("%s: I acquired a lock\n", arg);

	sleep(5);

	pthread_mutex_unlock(&lock);
	printf("%s: I going to release a lock\n", arg);
	
	
	
	//pthread_cond_wait(&cond1, &lock);
	thread1_result = 4;
	pthread_exit(&thread1_result);
}


int main(void)
{
	int retval = -1;
	void *p_retval;

	printf("I am in process\n");

	retval = pthread_create(&tid1, NULL, &my_thread, "Thread_1");
	if(retval < 0)
	{
		printf("Unable to create thread 1\n");
	}

	retval = pthread_create(&tid2, NULL, &my_thread, "Thread_2");
	if(retval < 0)
	{
		printf("Unable to create thread 1\n");
	}

	//printf("i am going to give the signal\n");
	//pthread_cond_signal(&cond1);


	retval = pthread_join(tid1, &p_retval);
	if(retval < 0)
	{
		printf("Failed to get thread status %d\n", retval);
	}
	else
	{
		printf("Pthread returned with %d\n", *(int*)p_retval);
	}
	
	retval = pthread_join(tid2, &p_retval);
	if(retval < 0)
	{
		printf("Failed to get thread status %d\n", retval);
	}
	else
	{
		printf("Pthread returned with %d\n", *(int*)p_retval);
	}

	return 0;
}