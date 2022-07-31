#include<linux/module.h>		//module_init(), module_exit()
#include<linux/sysfs.h> 
#include<linux/kobject.h> 

/*************** Sysfs functions **********************/
static ssize_t  sysfs_show(struct kobject *kobj, 
                        struct kobj_attribute *attr, char *buf);
static ssize_t  sysfs_store(struct kobject *kobj, 
                        struct kobj_attribute *attr,const char *buf, size_t count);

struct kobject *kobj_ref;

volatile int my_value = 0;

struct kobj_attribute etx_attr = __ATTR(ks_value, 0660, sysfs_show, sysfs_store);

/*
** This function will be called when we read the sysfs file
*/
static ssize_t sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        pr_info("Sysfs - Read!!!\n");
        return sprintf(buf, "%d", my_value);
}

/*
** This function will be called when we write the sysfsfs file
*/
static ssize_t sysfs_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
        pr_info("Sysfs - Write!!!\n");
        sscanf(buf,"%d",&my_value);
        return count;
}

int __init start_fun(void)
{
	printk(KERN_INFO "I am from starup fun\n");
//	kobj_ref = kobject_create_and_add("etx_sysfs",firmware_kobj); /*Creating a directory in /sys/firmware/ */
//  kobj_ref = kobject_create_and_add("etx_sysfs",fs_kobj); /*Creating a directory in /sys/fs/ */
	kobj_ref = kobject_create_and_add("ks_sysfs",kernel_kobj); /*Creating a directory in /sys/kernel/ */
	
	if(sysfs_create_file(kobj_ref,&etx_attr.attr))
	{
		pr_err("Cannot create sysfs file......\n");
		goto STEP_1;
	}
	return 0;

STEP_1:
	kobject_put(kobj_ref); 
	return -1;
}

void __exit cleanup_fun(void)
{
	printk(KERN_INFO "I am from cleanup fun\n");
	sysfs_remove_file(kernel_kobj, &etx_attr.attr);
	kobject_put(kobj_ref);
}

module_init(start_fun);
module_exit(cleanup_fun);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KS");
MODULE_VERSION("2.0");
MODULE_DESCRIPTION("Module explore");