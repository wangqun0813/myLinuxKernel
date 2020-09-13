ARCH ?= arm
CROSS_COMPILE ?= arm-linux-gnueabi-
#BASEINCLUDE ?= /lib/modules/`uname -r`/build

BASEINCLUDE ?= /home/rlk/rlk_basic/wq/origin/myLinuxKernel

hello_module-objs := hello.o
obj-m := hello_module.o

all:
	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) modules;
clean:
	$(MAKE) -C $(BASEINCLUDE) SUBDIRS=$(PWD) clean;
	rm -f *.ko;

