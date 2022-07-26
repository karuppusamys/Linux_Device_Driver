#include<linux/module.h>
//#include <linux/dev_printk.h>

int __init start_fun(void)
{
	printk(KERN_EMERG "I am emergency message\n");
	printk(KERN_ALERT "I am alert message\n");
	printk(KERN_CRIT "I am critical message\n");
	printk(KERN_ERR "I am error  message\n");
	printk(KERN_WARNING "I am warning message\n");
	printk(KERN_NOTICE "I am notice message\n");
	printk(KERN_INFO "I am info message\n");
	printk(KERN_DEBUG "I am debug  message\n");

	pr_emerg("I am emergency message\n");
	pr_alert("I am alert message\n");
	pr_crit("I am crit message\n");
	pr_err("I am error message\n");
	pr_warn("I am warning message\n");
	pr_notice("I am notice message\n");
	pr_info("I am info message\n");
	pr_debug("I am debug  message\n");

//	dev_emerg("I am emergency message\n");
//	dev_alert("I am alert message\n");
//	dev_crit("I am crit message\n");
//	dev_err("I am error message\n");
//	dev_warn("I am warning message\n");
//	dev_notice("I am notice message\n");
//	dev_info("I am info message\n");
//	dev_debug("I am debug  message\n")

	return 0;
}

void __exit cleanup_fun(void)
{

	printk(KERN_INFO "I am going to exit the module\n");
}

module_init(start_fun);
module_exit(cleanup_fun);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KS");
MODULE_VERSION("2.0");
MODULE_DESCRIPTION("Module explore");