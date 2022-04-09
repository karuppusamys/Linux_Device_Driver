#include <linux/module.h>

static int __init init_driver(void)
{
	printk(KERN_EMERG "I am emergency message\n");
	printk(KERN_ALERT "I am alert message\n");
	printk(KERN_CRIT "I am critical message\n");
	printk(KERN_ERR "I am error  message\n");
	printk(KERN_WARNING "I am warning message\n");
	printk(KERN_NOTICE "I am notice message\n");
	printk(KERN_INFO "I am info message\n");
	printk(KERN_DEBUG "I am debug  message\n");

	return 0;
}

static void __exit cleanup_driver(void)
{
	printk("Goodbye\n");
}
module_init(init_driver);
module_exit(cleanup_driver);

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Devi and Karuppu");
MODULE_VERSION("V1.0");
MODULE_DESCRIPTION("Simple LKM: Print kernel message with different log level/priority");
