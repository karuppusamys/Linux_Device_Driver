#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_t tid1, tid2;
int thread1_result;
int is_done = 1;

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void* my_thread(void *arg)
{
	printf("%s: I am going to wait for acquire a lock\n", arg);
	pthread_mutex_lock(&lock);
	printf("%s: I acquired a lock\n", arg);

	if(is_done == 1)
	{
		is_done = 0;
		printf("%s: I going to wait for signal\n", arg);
		pthread_cond_wait(&cond1, &lock);
		printf("%s: I got the signal\n", arg);
	}

	printf("%s: I going to sleep\n", arg);
	sleep(10);
	printf("%s: I going to release a lock\n", arg);
	pthread_mutex_unlock(&lock);
	
	
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

	sleep(1);
	printf("i am going to give the signal\n");
	pthread_cond_signal(&cond1);


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

//Reference: https://www.geeksforgeeks.org/condition-wait-signal-multi-threading/