#include<linux/module.h>
#include<linux/delay.h>
#include <linux/workqueue.h> 

/* Work structure */
static struct work_struct my_workqueue;

void workqueue_fn(struct work_struct *work); 
 
/*Workqueue Function*/
void workqueue_fn(struct work_struct *work)
{
        pr_info("Executing Workqueue Function\n");
}

int __init start_fun(void)
{
	printk(KERN_INFO "I am from starup fun\n");
	/*Creating work by Dynamic Method */
    INIT_WORK(&my_workqueue,workqueue_fn);

	schedule_work(&my_workqueue);
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