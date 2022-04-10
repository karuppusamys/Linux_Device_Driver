#include <linux/module.h>
#include <linux/gpio.h>

#define LED_BUTTON	20
#define DEBOUNCE_VAL_MS	10
#define PIN_STATE_LOW	0
#define PIN_STATE_HIGH	1

static int init_button(void)
{
	int retval = -1;

	/* Check whether give GPIO is vaild or not */
	retval = gpio_is_valid(LED_BUTTON);
	if(retval == false)
	{
		printk(KERN_ERR "GPIO %d is not available\n", LED_BUTTON);
		goto ERR_0;
	}

	/* Request the given gpio. This avoids other modules acessing this gpio once stated to used */
	retval = gpio_request(LED_BUTTON, "LED_BUTTON");
	if(retval < 0)
	{
		printk(KERN_ERR "Unable to request GPIO: %d \n", LED_BUTTON);
		goto ERR_0;
	}

	/* Set the direction for given gpio */
	retval = gpio_direction_output(LED_BUTTON, PIN_STATE_LOW);
	if(retval < 0)
	{
		printk(KERN_ERR "Unable to set direction for GPIO pin: %d \n", LED_BUTTON);
		goto ERR_1;
	}

	/* Export the gpio in to /sys/class/gpio. Second parameter is specifing
		the pin direction change acess from user space via sysfs */
	retval = gpio_export(LED_BUTTON, true);
	if(retval < 0)
	{
		printk(KERN_WARNING "Unable to export the GPIO pin: %d, Error: %d\n", LED_BUTTON, retval);
	}

	/* Get the sleep state of given gpio's controller */
	retval = gpio_cansleep(LED_BUTTON);
	if(retval == false)
	{
		printk(KERN_INFO "GPIO controller will not sleep\n");
		gpio_set_value(LED_BUTTON, PIN_STATE_HIGH);
	}
	else
	{
		printk(KERN_INFO "GPIO controller may sleep\n");
		gpio_set_value_cansleep(LED_BUTTON, PIN_STATE_HIGH);
	}

	printk(KERN_NOTICE "Set GPIO %d state as %d\n", LED_BUTTON, PIN_STATE_HIGH);
	return 0;

ERR_1:
	gpio_free(LED_BUTTON);

ERR_0:
	return -1;
}

static void exit_button(void)
{
	gpio_unexport(LED_BUTTON);
	gpio_free(LED_BUTTON);
	printk(KERN_INFO "GPIOs are released\n");
}

module_init(init_button);
module_exit(exit_button);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Devi and Karuppu");
MODULE_VERSION("V1.0");
MODULE_DESCRIPTION("Simple LKM: Change the state of output pin");