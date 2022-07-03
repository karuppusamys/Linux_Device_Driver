#include<linux/module.h>	//module_init(), module_exit()
#include<linux/kthread.h>	//kthread_run() //kthread_create()
#include<linux/delay.h>		//msleep()

static struct task_struct *my_task_struct;

int kthread_fun1(void *arg)
{
	while(!kthread_should_stop())
	{
		printk(KERN_INFO "I am from kthread\n");
		msleep(1000);
		
	}
	printk(KERN_INFO "I am going to close kthread\n");
	do_exit(1);
}

static int __init register_LKM(void)
{
	printk(KERN_INFO "I am going to register the LKM\n");

	my_task_struct = kthread_create(kthread_fun1, "TEST", "Kthread_1");
	
	wake_up_process(my_task_struct);
	
	return 0;
}

static void __exit unregister_LKM(void)
{
	printk(KERN_WARNING "I am going to unregister the LKM\n");
	kthread_stop(my_task_struct);
}

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_AUTHOR("KS");
MODULE_DESCRIPTION("This module creates and run the kernel thread using single API");

module_init(register_LKM);
module_exit(unregister_LKM);