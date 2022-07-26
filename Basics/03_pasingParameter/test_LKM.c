#include<linux/module.h>
#include<linux/moduleparam.h>

int shared_var, shared_arr[3];

module_param(shared_var, int, S_IWUSR|S_IRUSR);
module_param_array(shared_arr, int, NULL, S_IRUSR|S_IWUSR);

int __init start_fun(void)
{
	printk(KERN_INFO "I am from starup fun\n");
	printk(KERN_INFO "Integer value: %d\n", shared_var);
	printk(KERN_INFO "Integer values are: %d, %d, %d\n", shared_arr[0], shared_arr[1], shared_arr[2]);
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