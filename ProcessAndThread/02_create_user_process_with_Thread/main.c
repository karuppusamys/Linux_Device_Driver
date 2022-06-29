#include<stdio.h>
#include<pthread.h>

pthread_t tid1;
int thread1_result;

void* thread1(void *arg)
{
	unsigned int Cnt = 0;

	printf("I am in thread\n");

	Cnt = 0;
	while(Cnt < 0x0000FFFF)
	{
		printf("I am in thread count - %u\n", Cnt);
		Cnt++;
	}
	thread1_result = 4;
	pthread_exit(&thread1_result);
}


int main(void)
{
	int retval = -1;
	void *p_retval;

	printf("I am in process\n");

	retval = pthread_create(&tid1, NULL, &thread1, NULL);
	if(retval < 0)
	{
		printf("Unable to create thread\n");
	}

	retval = pthread_join(tid1, &p_retval);
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