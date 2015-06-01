TARGET		:=arm
BIN		:=$(TARGET).bin
START		:=start.o main.o
OBJS		:=clock.o
LD_ADDR		:=0x50000000
LD_LDS		:=./ld.lds
###########################################
CROSS_COMPILE 	:=arm-linux-

CC		:=$(CROSS_COMPILE)gcc
AS		:=$(CROSS_COMPILE)as
LD		:=$(CROSS_COMPILE)ld
OBJCOPY		:=$(CROSS_COMPILE)objcopy
OBJDUMP		:=$(CROSS_COMPILE)objdump
NM		:=$(CROSS_COMPILE)nm

RM		:=rm -rf	

CFLAGS		:=-I./include -Wall
LDFLAGS		:=
###############################################
#make === make all
all:$(TARGET)
	$(OBJCOPY) -O binary $< $(BIN)
	$(NM) $< >System.map
	$(RM) $<
		
	sudo ./down.sh

$(TARGET):$(START) $(OBJS)
	$(LD) $^ -o $@ -Ttext $(LD_ADDR)
clean:
	$(RM) $(START) $(OBJS) $(BIN)










