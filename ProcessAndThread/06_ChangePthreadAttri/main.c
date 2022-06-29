//Refernce : https://users.cs.cf.ac.uk/dave/C/node30.html
//Reference : https://users.cs.cf.ac.uk/dave/C/node29.html#SECTION002910000000000000000
// Reference for basics: https://users.cs.cf.ac.uk/dave/C/
//Reference : https://www.tutorialspoint.com/unix_system_calls/fork.htm
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sched.h>
#include <sys/resource.h> 

pthread_t tid1;
int result;
int int_buf;
struct sched_param param;
void *stackbase;
int stack_size;

void* thread1(void *arg)
{
	unsigned int Cnt = 0;
	pthread_t my_tid;
//	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
//	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

	my_tid = pthread_self(); //
	Cnt = 0;
	//while(Cnt < 0x0000FFFF)
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
	
	/* get detachstate of thread */
	retval = pthread_attr_getdetachstate(&tattr, &int_buf);
	if(retval < 0)
	{
		printf("Unable to Get the detach state of thread\n");
	}
	else
	{
		printf("Detach state of thread - %d\n", int_buf);
	}


	retval = pthread_attr_setinheritsched(&tattr, PTHREAD_EXPLICIT_SCHED);
	//retval = pthread_attr_setinheritsched(&tattr, PTHREAD_INHERIT_SCHED);
	if(retval < 0)
	{
		printf("Failed to set the inherit type of schedule police\n");
	}
	if(retval < 0)
	{
		printf("Unable to Get the inherit type of schedule police - %d\n", retval);
	}
	else
	{
		printf("Schedule inherit type - %d\n", int_buf);
	}



	retval = pthread_attr_setscope(&tattr, PTHREAD_SCOPE_SYSTEM);
	//retval = pthread_attr_setscope(&tattr, PTHREAD_SCOPE_PROCESS);
	if(retval < 0)
	{
		printf("Failed to set the thread schedule scope\n");
	}
	
	retval = pthread_attr_getscope(&tattr, &int_buf);
	if(retval < 0)
	{
		printf("Unable to Get the schedule scop of thread - %d\n", retval);
	}
	else
	{
		printf("Schedule scope of thread - %d\n", int_buf);
	}

	retval = pthread_attr_setschedpolicy(&tattr, SCHED_OTHER);
	//retval = pthread_attr_setschedpolicy(&tattr, SCHED_FIFO);
	//retval = pthread_attr_setschedpolicy(&tattr, SCHED_RR);
	if(retval < 0)
	{
		printf("Failed to set the scheduling police\n");
	}
	retval = pthread_attr_getschedpolicy(&tattr, &int_buf);
	if(retval < 0)
	{
		printf("Unable to Get the scheduling police - %d\n", retval);
	}
	else
	{
		printf("Scheduling police - %d\n", int_buf);
	}



	param.sched_priority = 30;
	retval = pthread_attr_setschedparam(&tattr, &param);
	if(retval < 0)
	{
		printf("Failed to set the schedule parameter (priority)\n");
	}

	param.sched_priority = 1; //Reset
	retval = pthread_attr_getschedparam(&tattr, &param);
	if(retval < 0)
	{
		printf("Unable to Get the schedule param (priority) - %d\n", retval);
	}
	else
	{
		printf("Scheduling param (priority) - %d\n", param.sched_priority);
	}

	//stack_size = PTHREAD_STACK_MIN + 0x4000;
	//retval = pthread_attr_setstacksize(&tattr, stacksize);
	//pthread_attr_getstacksize(&tattr, &stack_size);

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