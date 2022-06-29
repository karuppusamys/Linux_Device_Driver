#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sched.h>
#include <sys/resource.h> /* for getpriority() */
//https://www.tutorialspoint.com/unix_system_calls/fork.htm
pthread_t tid1;
int result;

void* thread1(void *arg)
{
	unsigned int Cnt = 0;
	pthread_t my_tid;
//	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
//	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	
	my_tid = pthread_self(); //
	Cnt = 0;
	while(Cnt < 0x0000FFFF)
	{
		printf("I am in thread - %u\n", Cnt);
		Cnt++;
	}
	result = 8;
	pthread_exit(&result);

	return 0;
}
int main(void)
{
	int retval = -1;
	unsigned int Cnt = 0;
	pthread_attr_t tattr;
	void *p_retval;

	printf("I am in main\n");
	
	retval = pthread_attr_init(&tattr);
	if(retval < 0)
	{
		printf("Unable to initialize thread attribute\n");
	}
	
	//pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
	pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_JOINABLE);

	retval = pthread_create(&tid1, &tattr, &thread1, NULL);
	if(retval < 0)
	{
		printf("Unable to create thread\n");
	}
	
	Cnt = 0;
	//while(Cnt < 0x000FFFFF)
	{
		printf("I am in process - %u\n", Cnt);
		Cnt++;
	}

//	retval = pthread_cancel(tid1);
	{
//		printf("Unable to cancel the thread - %d\n", retval);
	}

	retval = pthread_join(tid1, &p_retval);
	printf("Pthread returned with %d, %d\n", *(int*)p_retval, retval);
	
	retval = pthread_attr_destroy(&tattr);
	if(retval < 0)
	{
		printf("Unable to destroy thread attribute\n");
	}
	printf("I am in end of main\n");

	return 0;
}