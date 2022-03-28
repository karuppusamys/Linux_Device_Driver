#include <linux/module.h>

static int __init ModuleInit(void) 
{
	printk("Hello world!\n");
	return 0;
}

static void __exit ModuleExit(void) 
{
	printk("Goodbye\n");
}
module_init(ModuleInit);
module_exit(ModuleExit);

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Devi and Karuppu");
MODULE_VERSION("V1.0");
MODULE_DESCRIPTION("Simple LKM: Hello world");
