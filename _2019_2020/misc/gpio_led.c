#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h> 

#include <linux/gpio.h>
#ifdef CONFIG_OF
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_platform.h>
#endif

#include <linux/cdev.h>  
#include <linux/fs.h>


#define GPIO_LOW 0
#define GPIO_HIGH 1


static int gpio;
static dev_t gpio_led_dev_num;  
static struct cdev gpio_led_dev;    
static int gpio_led_open(struct inode *node, struct file *filep)  
{  
	gpio_direction_output(gpio, GPIO_HIGH);
	printk ("gpio_led is open!\n");            
	return 0;  
}

static ssize_t gpio_led_read (struct file *filep, char __user *buf, size_t count, loff_t *f_pos)  
{          
	gpio_set_value(gpio,GPIO_HIGH); 
	printk("gpio_led is read!\nthe led lever is : %d\n",gpio_get_value(gpio));  
	return 0;  
}

static ssize_t gpio_led_write (struct file *filep, const char __user *buf, size_t count, loff_t *f_pos)  
{  
	gpio_set_value(gpio,GPIO_LOW);
	printk("gpio_led is written!\nthe led lever is : %d\n",gpio_get_value(gpio));
	return 0;  
}

static ssize_t gpio_led_release (struct inode *, struct file *)
{  
	gpio_direction_input(gpio);
	printk ("gpio_led is released!\n");
	return 0;  
}

static struct file_operations gpio_led_fops = {  
	.read		= gpio_led_read,  
	.write		= gpio_led_write,  
	.open		= gpio_led_open, 
	.release	= gpio_led_release,
	.owner		= THIS_MODULE  
};

static int gpio_led_probe(struct platform_device *pdev)
{
	int ret = -1;
	int res; 
	int i;
	enum of_gpio_flags flag;
	 
	struct device_node *gpio_led_node = pdev->dev.of_node;

	printk("%s-%d: enter\n",__FUNCTION__,__LINE__);

	gpio = of_get_named_gpio_flags(gpio_led_node,"led", 0, &flag);
	if (!gpio_is_valid(gpio)){
		printk("hello: invalid gpio : %d\n",gpio);
		return -1;
	} 
	ret = gpio_request(gpio, "gpio_led");
	if (ret != 0) {
		gpio_free(gpio);
		return -EIO;
	}

	gpio_direction_output(gpio, GPIO_LOW);
	gpio_set_value(gpio,GPIO_HIGH);
	gpio_direction_input(gpio);

	printk("%s-%d: exit\n",__FUNCTION__,__LINE__);

	res = alloc_chrdev_region(&gpio_led_dev_num, 0, 1, "gpio_led_dev");
	if (res < 0)
		return res;
	cdev_init (&gpio_led_dev,&gpio_led_fops);
	cdev_add (&gpio_led_dev,gpio_led_dev_num, 1);

	printk ("gpio_led_dev is init\n");

	return 0;
}


static int gpio_led_remove(struct platform_device *pdev)
{
	cdev_del (&gpio_led_dev); 
	unregister_chrdev_region(gpio_led_dev_num, 1);
	printk ("gpio_led_dev is exit\n");
	gpio_free(gpio);
	return 0;
}
#ifdef CONFIG_OF
static const struct of_device_id of_gpio_led_match[] = {
	{ .compatible = "firefly,gpio_led" },
	{ /* Sentinel */ }
};
#endif

static struct platform_driver gpio_led_driver = {
	.probe		= gpio_led_probe,
	.remove		= gpio_led_remove,
	.driver		= {
		.name		= "firefly_gpio",
		.owner		= THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table	= of_gpio_led_match,
#endif
	},

};

static int __init gpio_led_init(void)
{
    printk(KERN_INFO "Enter %s\n", __FUNCTION__);
    return platform_driver_register(&gpio_led_driver);
    return 0;
}

static void __exit gpio_led_exit(void)
{
	platform_driver_unregister(&gpio_led_driver);
	printk("Exit Hello world\n");
}

//subsys_initcall(hello_init);
module_init(gpio_led_init);
module_exit(gpio_led_exit);

MODULE_AUTHOR("lsb <583160382@qq.com>");
MODULE_DESCRIPTION("gpio_led_driver");
MODULE_LICENSE("GPL");

