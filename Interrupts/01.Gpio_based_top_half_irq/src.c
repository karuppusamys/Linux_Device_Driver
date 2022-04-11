#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define LED_BUTTON	20
#define PUSH_BUTTON	21
#define DEBOUNCE_VAL_MS	10
#define PIN_STATE_LOW	0
#define PIN_STATE_HIGH	1

unsigned int irqNumber;

static irqreturn_t gpio_irq_handler(int IrqNum, void *dev_id) 
{
	static int IntCnt = 0;
	IntCnt++;
	printk(KERN_INFO "Total interrupt count %d\n", IntCnt);
	if(IntCnt%2 == 0)
	{
		gpio_set_value(LED_BUTTON, PIN_STATE_HIGH);
	}
	else
	{
		gpio_set_value(LED_BUTTON, PIN_STATE_LOW);
	}
	return IRQ_HANDLED;
}

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
	retval = gpio_is_valid(LED_BUTTON);
	if(retval == false)
	{
		printk(KERN_ERR "GPIO %d is not available\n", LED_BUTTON);
		goto ERR_0;
	}

	/* Request the given gpio. This avoids other modules acessing this gpio once stated to used */
	retval = gpio_request(PUSH_BUTTON, "PUSH_BUTTON");
	if(retval < 0)
	{
		printk(KERN_ERR "Unable to request GPIO: %d \n", PUSH_BUTTON);
		goto ERR_0;
	}
	retval = gpio_request(LED_BUTTON, "LED_BUTTON");
	if(retval < 0)
	{
		printk(KERN_ERR "Unable to request GPIO: %d \n", LED_BUTTON);
		goto ERR_1;
	}

	/* Set the direction for given gpio */
	retval = gpio_direction_input(PUSH_BUTTON);
	if(retval < 0)
	{
		printk(KERN_ERR "Unable to set direction for GPIO pin: %d \n", PUSH_BUTTON);
		goto ERR_2;
	}
	retval = gpio_direction_output(LED_BUTTON, PIN_STATE_LOW);
	if(retval < 0)
	{
		printk(KERN_ERR "Unable to set direction for GPIO pin: %d \n", LED_BUTTON);
		goto ERR_2;
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
	retval = gpio_export(LED_BUTTON, true);
	if(retval < 0)
	{
		printk(KERN_WARNING "Unable to export the GPIO pin: %d, Error: %d\n", LED_BUTTON, retval);
	}

	//Get the IRQ number for our GPIO
	irqNumber = gpio_to_irq(PUSH_BUTTON);
	
	if (request_irq(irqNumber, (void *)gpio_irq_handler, IRQF_TRIGGER_RISING, "button_device", NULL))    //IRQF_TRIGGER_RISING | IRQF_TRIGGER_HIGH
	{                   
		printk(KERN_ERR "Unable to register irq handler for irq no: %d\n", irqNumber);
		goto ERR_3;
	}

	printk(KERN_NOTICE "Scessfully Configured the GPIO PIN %d as interrupt and GPIO pin %d as output pin for LED \n", PUSH_BUTTON, LED_BUTTON);
	return 0;
ERR_3:
	gpio_unexport(PUSH_BUTTON);
	gpio_unexport(LED_BUTTON);
ERR_2:
	gpio_free(LED_BUTTON);
	
ERR_1:
	gpio_free(PUSH_BUTTON);

ERR_0:
	return -1;
}

static void exit_button(void)
{
	gpio_unexport(PUSH_BUTTON);
	gpio_unexport(LED_BUTTON);
	gpio_free(PUSH_BUTTON);
	gpio_free(LED_BUTTON);
	printk(KERN_INFO "GPIOs are released\n");
}

module_init(init_button);
module_exit(exit_button);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Devi and Karuppu");
MODULE_VERSION("V1.0");
MODULE_DESCRIPTION("Simple LKM: Print the input state of gpio pin");