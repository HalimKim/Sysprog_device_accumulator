KERNEL_VER = 4.19.66-v7+
KERNEL_DIR = /lib/modules/$(KERNEL_VER)/build

obj-m := sysprog_device.o

PWD := $(shell pwd)

all : 
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean : 
	make -C $(KERNEL_DIR) M=$(PWD) clean


