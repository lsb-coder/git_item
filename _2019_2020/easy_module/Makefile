ifneq ($(KERNELRELEASE),)
#module-objs := file1.o file.o 
obj-m :=easy_module.o
else 
KDIR :=/lib/modules/$(shell uname -r)/build	
PWD := $(shell pwd)
all:     
	$(MAKE) -C $(KDIR) M=$(PWD) modules 
	@rm -rf *.mod.* 
	@rm -rf .*.cmd 
	@rm -rf *.o 
	@rm -rf Module.* 
	@rm -rf *.order
clean: 
	rm -rf *.ko 
endif
