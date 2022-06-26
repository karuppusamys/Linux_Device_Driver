#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>


pthread_t tid1;

void* thread1(void *arg)
{
	unsigned int Cnt = 0;
	
	Cnt = 0;
	while(Cnt < 0x000FFFFF)
	{
		printf("I am in thread - %u\n", Cnt);
		Cnt++;
	}

	return 0;
}
int main(void)
{
	int retval = -1;
	
	unsigned int Cnt = 0;

	printf("I am in main\n");
	
	retval = pthread_create(&tid1, NULL, &thread1, NULL);
	if(retval < 0)
	{
		printf("Unable to create thread\n");
	}
	
	Cnt = 0;
	while(Cnt < 0x000FFFFF)
	{
		printf("I am in process - %u\n", Cnt);
		Cnt++;
	}
	
	//sleep(30);
	printf("I am in end of main\n");

	return 0;
}