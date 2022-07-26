#include<linux/module.h>
#include<linux/kdev_t.h> //MKDEV
#include <linux/fs.h>	//dev_t, register_chrdev_region, unregister_chrdev_region

dev_t dev_num = MKDEV(444, 0);

int __init start_fun(void)
{
	printk(KERN_INFO "I am from starup fun\n");
	
	//proto int register_chrdev_region(dev_t first, unsigned int count, char *name);
	register_chrdev_region(dev_num, 1, "my_test_device");  
	
	return 0;
}

void __exit cleanup_fun(void)
{
	printk(KERN_INFO "I am from cleanup fun\n");
	unregister_chrdev_region(dev_num, 1);  
}

module_init(start_fun);
module_exit(cleanup_fun);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KS");
MODULE_VERSION("2.0");
MODULE_DESCRIPTION("Module explore");