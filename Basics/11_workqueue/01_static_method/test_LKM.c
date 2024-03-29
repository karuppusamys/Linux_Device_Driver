#include<linux/module.h>
#include<linux/delay.h>
#include <linux/workqueue.h> 

void workqueue_fn(struct work_struct *work); 
 
/*Creating work by Static Method */
DECLARE_WORK(my_workqueue,workqueue_fn);
 
/*Workqueue Function*/
void workqueue_fn(struct work_struct *work)
{
        pr_info("Executing Workqueue Function\n");
}

int __init start_fun(void)
{
	printk(KERN_INFO "I am from starup fun\n");
	schedule_work(&my_workqueue);
//	ndelay(1000);
//	udelay(1000);
//	mdelay(1000);
//	usleep_range(500, 600);
	msleep(500);
	//ssleep(5);
	return 0;
}

void __exit cleanup_fun(void)
{
	printk(KERN_INFO "I am from cleanup fun\n");
}

module_init(start_fun);
module_exit(cleanup_fun);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KS");
MODULE_VERSION("2.0");
MODULE_DESCRIPTION("Module explore");