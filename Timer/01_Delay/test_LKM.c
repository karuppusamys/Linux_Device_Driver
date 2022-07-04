#include<linux/module.h>	//module_init(), module_exit()
#include<linux/kthread.h>	//kthread_run() //kthread_create()
#include<linux/delay.h>		//msleep()

static struct task_struct *my_task_struct;

int kthread_fun(void *arg)
{
	while(!kthread_should_stop())
	{
		printk(KERN_INFO "I am from kthread\n");
	//	ndelay(1000000000);	//void ndelay(unsigned long x)
	//	udelay(1000000);	//void udelay(unsigned long x)
	//	mdelay(1000);		//void mdelay(unsigned long x)
		
	//	usleep_range(1000000, 2000000);	//void usleep_range(unsigned long min, unsigned long max)
	//	msleep(1000);					//void msleep(unsigned int msecs);
		ssleep(1);						//void ssleep(unsigned int seconds)
	//	fsleep(1000000);				//void fsleep(unsigned long usecs)

	}
	printk(KERN_INFO "I am going to close kthread\n");
	do_exit(1);
}

static int __init register_LKM(void)
{
	printk(KERN_INFO "I am going to register the LKM\n");

	my_task_struct = kthread_create(kthread_fun, "TEST", "Kthread_1");
	
	wake_up_process(my_task_struct);
	
	return 0;
}

static void __exit unregister_LKM(void)
{
	printk(KERN_WARNING "I am going to unregister the LKM\n");
	kthread_stop(my_task_struct);
	//kthread_join(my_task_struct);
}

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_AUTHOR("KS");
MODULE_DESCRIPTION("This module creates and run the kernel thread using single API");

module_init(register_LKM);
module_exit(unregister_LKM);

// Command to see the process status: $(while true; do ps -eo pid,%cpu,psr,cmd | grep Kthread; sleep 1; clear; done)