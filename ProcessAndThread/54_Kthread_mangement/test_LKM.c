#include<linux/module.h>	//module_init(), module_exit()
#include<linux/kthread.h>	//kthread_run() //kthread_create()
#include<linux/delay.h>		//msleep()
#include<linux/sched.h>

#include <linux/cpu.h>
#include <linux/percpu.h>

static struct task_struct *my_task_struct;

int kthread_fun(void *arg)
{
	while(!kthread_should_stop())
	{
		printk(KERN_INFO "I am from kthread. Core: %d\n", get_cpu());
		ssleep(2);
	}
	printk(KERN_INFO "I am going to close kthread\n");
	do_exit(1);
}

static int __init register_LKM(void)
{
	static int current_cpu;

	printk(KERN_INFO "I am going to register the LKM. Core: %d\n", get_cpu());

	my_task_struct = kthread_create(kthread_fun, "TEST", "Kthread_1");

	current_cpu = get_cpu();
	current_cpu = 3;
	kthread_bind(my_task_struct, current_cpu);


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
MODULE_DESCRIPTION("This module creates and run the kernel thread using single API. And assign to desired single CPU");

module_init(register_LKM);
module_exit(unregister_LKM);

// Command to see the process status: $(while true; do ps -eo pid,%cpu,psr,cmd | grep Kthread; sleep 1; clear; done)
