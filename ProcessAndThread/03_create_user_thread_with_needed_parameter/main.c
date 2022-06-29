#include<stdio.h>		//printf, scanf
#include<pthread.h>		//pthread_create
#include <sched.h>		//pthread attribute update APIs

pthread_t tid1;
int thread1_result;
int int_buf;
struct sched_param param;
void *stackbase;
int stack_size;

void* thread1(void *arg)
{
	unsigned int Cnt = 0;
	pthread_t my_tid;

	my_tid = pthread_self(); //
	printf("I am in thread - %u\n", my_tid);

//	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
//	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

	Cnt = 0;
	while(Cnt < 0x00000005)
	{
		printf("I am in thread count - %u\n", Cnt);
		Cnt++;
	}
	thread1_result = 8;
	pthread_exit(&thread1_result);
}


int main(void)
{
	int retval = -1;
	pthread_attr_t tattr;
	void *p_retval;

	printf("I am in main\n");

	//Initalize thread attribute for set the needed parameters
	retval = pthread_attr_init(&tattr);
	if(retval < 0)
	{
		printf("Unable to initialize thread attribute\n");
	}


	//Set the pthread detach type
	//pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
	pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_JOINABLE);
	retval = pthread_attr_getdetachstate(&tattr, &int_buf);
	if(retval < 0)
	{
		printf("Unable to Get the detach state of thread\n");
	}
	else
	{
		printf("Detach state of thread - %d\n", int_buf);
	}


	//Set the scheduler police inherit type
	retval = pthread_attr_setinheritsched(&tattr, PTHREAD_EXPLICIT_SCHED);
	//retval = pthread_attr_setinheritsched(&tattr, PTHREAD_INHERIT_SCHED);
	if(retval < 0)
	{
		printf("Failed to set the inherit type of schedule police\n");
	}
	retval = pthread_attr_getinheritsched(&tattr, &int_buf);
	if(retval < 0)
	{
		printf("Unable to Get the inherit type of schedule police - %d\n", retval);
	}
	else
	{
		printf("Schedule inherit type - %d\n", int_buf);
	}


	//Set the scope of thread
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


	//Set the scheduling priority
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

	//Set the custom stack size for thread
	//stack_size = PTHREAD_STACK_MIN + 0x4000;
	//retval = pthread_attr_setstacksize(&tattr, stacksize);
	//pthread_attr_getstacksize(&tattr, &stack_size);

	retval = pthread_create(&tid1, &tattr, &thread1, NULL);
	if(retval < 0)
	{
		printf("Unable to create thread\n");
	}


//	retval = pthread_cancel(tid1);
	{
//		printf("Unable to cancel the thread - %d\n", retval);
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
	
	retval = pthread_attr_destroy(&tattr);
	if(retval < 0)
	{
		printf("Unable to destroy thread attribute\n");
	}

	printf("I am in end of main\n");

	return 0;
}

//Refernce : https://users.cs.cf.ac.uk/dave/C/node30.html
//Reference : https://users.cs.cf.ac.uk/dave/C/node29.html#SECTION002910000000000000000
//Reference for basics: https://users.cs.cf.ac.uk/dave/C/
//Reference : https://www.tutorialspoint.com/unix_system_calls/fork.htm