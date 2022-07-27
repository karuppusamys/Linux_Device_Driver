#include<linux/module.h>	//module_init(), module_exit()
#include<linux/kdev_t.h> 	//MKDEV
#include<linux/fs.h>		//dev_t, register_chrdev_region, unregister_chrdev_region
#include<linux/device.h>	//class_create
#include<linux/slab.h>		//kmalloc(), kfree()
#include<linux/proc_fs.h>
#define MEM_SIZE 10



dev_t dev_num;
struct class* my_class;
struct device* my_device;
static struct proc_dir_entry *parent;
static int len = 1;
uint8_t *kern_buff;

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

ssize_t my_read(struct file* myfile, char __user *buf, size_t lenth, loff_t *off)
{
	printk(KERN_INFO "I am from read\n");
	
	if(len)
    {
        len=0;
    }
    else
    {
        len=1;
        return 0;
    }

	if(copy_to_user(buf, kern_buff, MEM_SIZE))
	{
		printk(KERN_WARNING "Failed copy the data\n");
	}

	return lenth;
}

ssize_t my_write(struct file* myfile, const char *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "I am from write\n");
	if(copy_from_user(kern_buff, buf, MEM_SIZE))
	{
		printk(KERN_WARNING "Failed copy the data\n");
	}

	return len;
}


static struct proc_ops proc_fops = {
	.proc_open = my_open,
	.proc_read = my_read,
	.proc_write = my_write,
	.proc_release = my_close
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

	kern_buff = kmalloc(MEM_SIZE, GFP_KERNEL);
	
	if(kern_buff < 0)
	{
		printk(KERN_WARNING "Unable to allocate the memory\n");
		goto STEP_3;
	}
	
	/*Create proc directory. It will create a directory under "/proc" */
	parent = proc_mkdir("ks",NULL);
	
	if( parent == NULL )
	{
		pr_info("Error creating proc entry");
		goto STEP_4;
	}
	
	/*Creating Proc entry under "/proc/etx/" */
	proc_create("my_proc", 0666, parent, &proc_fops);
		
	return 0;
STEP_4:
	kfree(kern_buff);
STEP_3:
	device_destroy(my_class, dev_num);
STEP_2:
	class_destroy(my_class);
STEP_1:
	unregister_chrdev_region(dev_num, 1);
	return -1;
}

void __exit cleanup_fun(void)
{
	printk(KERN_INFO "I am from cleanup fun\n");
	proc_remove(parent);
	kfree(kern_buff);
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