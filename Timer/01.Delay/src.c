#include <linux/module.h>				// Moduel init and exit
#include <linux/kthread.h>				// kernel thread related calls
#include <linux/sched.h>				// wake_up_process 
#include <linux/delay.h>				// sleep and delay calls

static struct task_struct *my_thread1;
int my_fun1(void *pv);


int my_fun1(void *pv)
{
	unsigned int Cnt = 0;
	while(!kthread_should_stop())
	{
		printk(KERN_INFO "I am from thread: %u\n", Cnt);
		msleep(1000);
		Cnt++;
	}
	return 0;
}
static int __init init_driver(void)
{
	my_thread1 = kthread_create(my_fun1, NULL, "Testing");
	if(my_thread1)
	{
		wake_up_process(my_thread1);
	}
	else
	{
		printk(KERN_INFO "Not able to create thread\n");
		goto clean1;	
	}
	printk("Driver probed sucessfully\n");
	return 0;

clean1:
	return -1;
}

static void __exit cleanup_driver(void)
{
	kthread_stop(my_thread1);
	printk("Driver going to remove\n");
}
module_init(init_driver);
module_exit(cleanup_driver);

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Devi and Karuppu");
MODULE_VERSION("V1.0");
MODULE_DESCRIPTION("Simple LKM: Creating a thread");
