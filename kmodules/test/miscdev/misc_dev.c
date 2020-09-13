#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>

#define DEV_NAME "demo_miscdev"  //字符设备名称
static struct device *demo_miscdev;	//字符设备结构体
static int count = 1;	//字符设备数量

module_param(count, int, 0664);

static int demodev_open(struct inode *inode, struct file *filp)
{
	printk("%s\n", __func__);
	return 0;
}

static int demodev_release(struct inode *inode, struct file *filp)
{
	printk("%s\n", __func__);
	return 0;
}

static ssize_t demodev_read(struct file *filp, char __user *buf, size_t len, loff_t *ppos)
{
	printk("%s\n", __func__);
	return 0;
}

static ssize_t demodev_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_ops)
{
	printk("%s\n", __func__);
	return 0;
}


static struct file_operations demo_fops = {
	.owner = THIS_MODULE,
	.open = demodev_open,
	.release = demodev_release,
	.read = demodev_read,
	.write = demodev_write,
};

static struct miscdevice my_demo_miscdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name =  DEV_NAME,
	.fops = &demo_fops,
};

static int __init demo_device_init(void)
{
	int ret;

	ret = misc_register(&my_demo_miscdev);
	if (ret != 0){
		printk("register demo_miscdev failed.\n");
		return ret;
	}
	demo_miscdev = my_demo_miscdev.this_device;
	
	printk("demo_miscdev register success.\n");
	return 0;
}

static void __exit demo_device_exit(void)
{
	printk("removing demo misc device.\n");
	misc_deregister(&my_demo_miscdev);
}


module_init(demo_device_init);
module_exit(demo_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qun.wang");
MODULE_DESCRIPTION("Simple chracter device");
EXPORT_SYMBOL_GPL(count);
