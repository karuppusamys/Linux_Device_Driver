#include<stdio.h>		//printf, scanf
#include<pthread.h>		//pthread_create
#include <sched.h>		//pthread attribute update APIs
#include <sys/resource.h> // getpriority(), PRIO_PROCESS

pthread_t tid1;
int thread1_result;

void* thread1(void *arg)
{
	int retval = -1;
	unsigned int Cnt = 0;
	struct sched_param param;
	cpu_set_t mask;
	pthread_t my_tid;

	my_tid = pthread_self(); //
	printf("I am in thread - %u\n", my_tid);

	
	//Priority range for difference scheduling polices
	printf("Valid priority range for SCHED_OTHER: %d - %d\n", sched_get_priority_min(SCHED_OTHER), sched_get_priority_max(SCHED_OTHER));
    printf("Valid priority range for SCHED_FIFO: %d - %d\n", sched_get_priority_min(SCHED_FIFO), sched_get_priority_max(SCHED_FIFO));
    printf("Valid priority range for SCHED_RR: %d - %d\n", sched_get_priority_min(SCHED_RR), sched_get_priority_max(SCHED_RR));


	//Read the current process priority
	retval = getpriority(PRIO_PROCESS, 0);
	printf("Current process schedule priority: %d\n",retval);
	
	retval = setpriority(PRIO_PROCESS, 0, 5);
	if(retval < 0)
	{
		printf("Failed to set priority: %d\n",retval);
	}
	else
	{
		retval = getpriority(PRIO_PROCESS, 0);
		printf("Process schedule priority after update: %d\n",retval);
	}



	//Read the current process priority
	retval = sched_getparam(0, &param);
	printf("process schedule priority read from param: %d\n", param.sched_priority);

	param.sched_priority = 0;
	retval = sched_setparam(0, &param);
	if(retval < 0)
	{
		printf("Failed to update the schedule parameters %d\n", retval);
	}
	else
	{
		retval = sched_getparam(0, &param);
		printf("process schedule priority after update param: %d\n", param.sched_priority);
	}

	
	//Read the currently shedule police
	retval = sched_getscheduler(0);
	printf("Process shedule policy: %d\n", retval);
	//Integer values for different scheduler polices
	printf("Process shedule policy value for SCHED_OTHER:%d. SCHED_FIFO: %d. SCHED_RR: %d\n", SCHED_OTHER, SCHED_FIFO, SCHED_RR);


	retval = sched_setscheduler(0, SCHED_OTHER, &param);
	if(retval < 0)
	{
		printf("Unable to change sheduler police: %d\n", retval);
	}
	else
	{
		//Read the currently shedule police
		retval = sched_getscheduler(0);
		printf("Process shedule policy after update: %d\n", retval);
	}

	//Get and set the process affnity
	//sched_getaffinity(0, sizeof(cpu_set_t), &mask);
	//CPU_ZERO(&mask);	//clean all
    //CPU_SET(0, &mask);	//Set the 0th core
	//CPU_SET(0, &mask);	//Set the 1core core
	//retval = sched_setaffinity(0, sizeof(cpu_set_t), &mask);
	//printf("Process affnity: %u\n", mask);
	
	Cnt = 0;
	//while(Cnt < 0x000FFFFF)
	{
		printf("I am in thread - %u\n", Cnt);
		Cnt++;
	}

	thread1_result = 8;
	pthread_exit(&thread1_result);;
}


int main(void)
{
	int retval = -1;
	void *p_retval;

	printf("I am in main\n");
	
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


//Reference: https://www.tutorialspoint.com/unix_system_calls/fork.htm