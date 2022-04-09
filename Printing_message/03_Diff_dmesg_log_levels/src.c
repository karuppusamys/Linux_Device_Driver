#include <linux/module.h>
#include <linux/dev_printk.h>

static int __init init_driver(void)
{
	pr_emerg("I am emergency message\n");
	pr_alert("I am alert message\n");
	pr_crit("I am crit message\n");
	pr_err("I am error message\n");
	pr_warn("I am warning message\n");
	pr_notice("I am notice message\n");
	pr_info("I am info message\n");
	pr_debug("I am debug  message\n");

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
MODULE_DESCRIPTION("Simple LKM: Print the kernel message using pr_ family functions");
