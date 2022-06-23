#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid1;

void* thread1(void *arg)
{
	printf("I am in thread1\n");

	return 0;
}
int main(void)
{
	int retval = -1;

	printf("I am in main\n");
	
	retval = pthread_create(&tid1, NULL, &thread1, NULL);
	if(retval < 0)
	{
		printf("Unable to create thread\n");
	}
	
	sleep(1);
	
	printf("I am in end of main\n");

	return 0;
}