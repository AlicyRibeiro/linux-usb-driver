obj-m += meu_driver_usb.o

MODULES_DIR=${PWD}

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(MODULES_DIR) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(MODULES_DIR) clean
