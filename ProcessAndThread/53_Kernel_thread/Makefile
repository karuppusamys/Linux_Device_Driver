obj-m += test_LKM.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


#obj-m = test_LKM.o

#KPATH = /lib/modules/$(shell uname -r)/build
#PWD = $(shell pwd)

#all:
#	make -C $(KPATH) M=$(PWD) modules

#clean:
#	make -C $(KPATH) M=$(PWD)  clean

