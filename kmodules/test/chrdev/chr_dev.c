#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEV_NAME "demo_device"  //字符设备名称
static struct cdev *demo_dev;	//字符设备结构体
static dev_t devno;		//字符设备号
static int count = 1;	//字符设备数量

module_param(count, int, 0664);

static int demodev_open(struct inode *inode, struct file *filp)
{
	int major = MAJOR(inode->i_rdev);
	int minor = MINOR(inode->i_rdev);

	printk("%s: major=%d, minor=%d\n", __func__, major, minor);
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


static struct file_operations demodev_fops = {
	.owner = THIS_MODULE,
	.open = demodev_open,
	.release = demodev_release,
	.read = demodev_read,
	.write = demodev_write,
};

static int __init demo_device_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&devno, 0, count, DEV_NAME);
	if (ret != 0){
		printk("failed to alloc chrdev region.\n");
		return ret;
	}
	
	demo_dev = cdev_alloc();
	if (!demo_dev){
		printk("demo device alloc failed.\n");
		goto unregister_chrdev;
	}
	cdev_init(demo_dev, &demodev_fops);
	ret = cdev_add(demo_dev, devno, count);
	if (ret != 0){
		printk("cdev add failed.\n");
		goto cdev_fail;
	}

	printk("%d demo_cdev register success.\n", count);
	printk("Major number:%d, Minor number:%d\n", MAJOR(devno), MINOR(devno));
	return 0;

cdev_fail:
	cdev_del(demo_dev);
unregister_chrdev:
	unregister_chrdev_region(devno, count);
	return ret;
}

static void __exit demo_device_exit(void)
{
	printk("removing demo device.\n");
	if (demo_dev){
		cdev_del(demo_dev);
	}
	unregister_chrdev_region(devno, count);
}


module_init(demo_device_init);
module_exit(demo_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qun.wang");
MODULE_DESCRIPTION("Simple chracter device");
EXPORT_SYMBOL_GPL(count);
