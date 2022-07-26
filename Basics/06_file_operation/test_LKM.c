#include<linux/module.h>
#include<linux/kdev_t.h> 	//MKDEV
#include <linux/fs.h>		//dev_t, register_chrdev_region, unregister_chrdev_region
#include <linux/device.h>	//class_create
#include <linux/cdev.h>

dev_t dev_num;
struct class* my_class;
struct device* my_device;
struct cdev my_cdev;

int my_open(struct inode* myinode, struct file* myfile);
int my_close(struct inode* myinode, struct file* myfile);
ssize_t my_read(struct file* myfile, char __user *buf, size_t len, loff_t *off);
ssize_t my_write(struct file* myfile, const char *buf, size_t len, loff_t *off);

int my_open(struct inode* myinode, struct file* myfile)
{
	printk(KERN_INFO "I am from open\n");
	return 0;
}

int my_close(struct inode* myinode, struct file* myfile)
{
	printk(KERN_INFO "I am from close\n");
	return 0;
}

ssize_t my_read(struct file* myfile, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "I am from read\n");
	return 0;
}

ssize_t my_write(struct file* myfile, const char *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "I am from write\n");
	return len;
}

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open =	my_open,
	.read = my_read,
	.write = my_write,
	.release = my_close,
};

int __init start_fun(void)
{
	int retval = -1;

	//int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);
	retval = alloc_chrdev_region(&dev_num, 0, 1, "my_test_device");
	
	if(retval < 0)
	{
		printk(KERN_WARNING "Failed to allocate the device numbers\n");
		return -1;
	}
	printk(KERN_INFO "allocated major number: %d  \nallocated minorm number: %d\n", MAJOR(dev_num), MINOR(dev_num));
	
	my_class = class_create(THIS_MODULE, "test_class");
	
	if(my_class == NULL)
	{
		printk(KERN_WARNING "Unable to create class\n");
		goto STEP_1;
	}

	//struct device *device_create(struct *class, struct device *parent, dev_t dev, void * drvdata, const char *fmt, ...);
	my_device = device_create(my_class, NULL, dev_num, NULL, "my_test_dev");
	if(my_device == NULL)
	{
		printk(KERN_WARNING "Unable to create device structure\n");
		goto STEP_2;
	}
	
	cdev_init(&my_cdev, &fops);
	
	cdev_add(&my_cdev, dev_num, 1);

	return 0;

STEP_2:
	class_destroy(my_class);
STEP_1:
	unregister_chrdev_region(dev_num, 1);
	return -1;
}

void __exit cleanup_fun(void)
{
	printk(KERN_INFO "I am from cleanup fun\n");
	cdev_del(&my_cdev);
	device_destroy(my_class, dev_num);
	class_destroy(my_class);
	unregister_chrdev_region(dev_num, 1);  
}

module_init(start_fun);
module_exit(cleanup_fun);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KS");
MODULE_VERSION("2.0");
MODULE_DESCRIPTION("Module explore");