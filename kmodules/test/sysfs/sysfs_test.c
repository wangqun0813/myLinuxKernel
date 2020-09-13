#include <linux/init.h>
#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>

static int foo;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	sprintf(buf, "%d", foo);
	return 0;
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	sscanf(buf, "%d", &foo);
	return count;
}

static struct kobj_attribute foo_attr = __ATTR(foo, 0664, foo_show, foo_store);
static struct attribute *attrs[] = {
	&foo_attr.attr,
	NULL
};
static struct attribute_group attr_group = {
	.attrs = attrs,
};
static struct kobject *example_kobj;

static int __init example_init(void)
{
	int ret;

	example_kobj =kobject_create_and_add("example_kobj", kernel_kobj);
	ret = sysfs_create_group(example_kobj,&attr_group);
	if (ret){
		kobject_put(example_kobj);
	}
	return ret;
}



static void __exit example_exit(void)
{
	kobject_put(example_kobj);
}


module_init(example_init);
module_exit(example_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("qun.wang");
MODULE_DESCRIPTION("example sysfs kobj");
MODULE_ALIAS("example sysfs");
