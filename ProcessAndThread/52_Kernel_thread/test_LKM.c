#include<linux/module.h>	//module_init, module_exit
#include<linux/kthread.h>  //kthread_run //kthread_create

static struct task_struct *my_task_struct;

int kthread_fun1(void *arg)
{
	printk(KERN_INFO "I am from kthread\n");
	return 0;
}

static int __init register_LKM(void)
{
	//int retval = -1;
	printk(KERN_INFO "I am going to register the LKM\n");

	my_task_struct = kthread_run(kthread_fun1, "TEST", "Kthread_1");
	
	return 0;
}

static void __exit unregister_LKM(void)
{
	printk(KERN_WARNING "I am going to unregister the LKM\n");
}

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_AUTHOR("KS");
MODULE_DESCRIPTION("This module creates and runs using different APIs");

module_init(register_LKM);
module_exit(unregister_LKM);