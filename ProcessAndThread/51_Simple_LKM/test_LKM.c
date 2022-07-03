#include<linux/module.h>

static int __init register_LKM(void)
{
	printk(KERN_INFO "I am going to register the LKM\n");
	return 0;
}

static void __exit unregister_LKM(void)
{
	printk(KERN_WARNING "I am going to unregister the LKM\n");
}
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_AUTHOR("KS");
MODULE_DESCRIPTION("This is a simple linux kernel module");

module_init(register_LKM);
module_exit(unregister_LKM);