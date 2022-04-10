#include <linux/module.h>
#include <linux/gpio.h>

#define PUSH_BUTTON	21
#define DEBOUNCE_VAL_MS	10

static int init_button(void)
{
	int retval = -1;

	/* Check whether give GPIO is vaild or not */
	retval = gpio_is_valid(PUSH_BUTTON);
	if(retval == false)
	{
		printk(KERN_ERR "GPIO %d is not available\n", PUSH_BUTTON);
		goto ERR_0;
	}

	/* Request the given gpio. This avoids other modules acessing this gpio once stated to used */
	retval = gpio_request(PUSH_BUTTON, "PUSH_BUTTON");
	if(retval < 0)
	{
		printk(KERN_ERR "Unable to request GPIO: %d \n", PUSH_BUTTON);
		goto ERR_0;
	}

	/* Set the direction for given gpio */
	retval = gpio_direction_input(PUSH_BUTTON);
	if(retval < 0)
	{
		printk(KERN_ERR "Unable to set direction for GPIO pin: %d \n", PUSH_BUTTON);
		goto ERR_1;
	}

	/* Set the debounce value for given gpio, This avoid the glitchs/noises on input pin.
		Value should be set based on the harware environment */
	retval = gpio_set_debounce(PUSH_BUTTON, DEBOUNCE_VAL_MS);
	if(retval < 0)
	{
		printk(KERN_WARNING "Not able to set the debounce value for GPIO: %d, Error: %d\n", PUSH_BUTTON, retval);
	}

	/* Export the gpio in to /sys/class/gpio. Second parameter is specifing
		the pin direction change acess from user space via sysfs */
	retval = gpio_export(PUSH_BUTTON, true);
	if(retval < 0)
	{
		printk(KERN_WARNING "Unable to export the GPIO pin: %d, Error: %d\n", PUSH_BUTTON, retval);
	}

	/* Get the sleep state of given gpio's controller */
	retval = gpio_cansleep(PUSH_BUTTON);
	if(retval == false)
	{
		printk(KERN_INFO "GPIO controller will not sleep\n");
		retval = gpio_get_value(PUSH_BUTTON);
	}
	else
	{
		printk(KERN_INFO "GPIO controller may sleep\n");
		retval = gpio_get_value_cansleep(PUSH_BUTTON);
	}

	printk(KERN_NOTICE "Present state of GPIO: %d is %d\n", PUSH_BUTTON, retval);
	return 0;

ERR_1:
	gpio_free(PUSH_BUTTON);

ERR_0:
	return -1;
}

static void exit_button(void)
{
	gpio_unexport(PUSH_BUTTON);
	gpio_free(PUSH_BUTTON);
	printk(KERN_INFO "GPIOs are released\n");
}

module_init(init_button);
module_exit(exit_button);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Devi and Karuppu");
MODULE_VERSION("V1.0");
MODULE_DESCRIPTION("Simple LKM: Print the input state of gpio pin");