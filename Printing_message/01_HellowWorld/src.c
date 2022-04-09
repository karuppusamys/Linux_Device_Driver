#include <linux/module.h>

static int __init init_driver(void)
{
	printk("Hello world!\n");
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
MODULE_DESCRIPTION("Simple LKM: Hello world");
