CC      := arm-linux-gcc
CFLAGS  += -march=armv7-a

sources := $(shell ls *.c)
all     := $(sources:%.c=%)
asm     := $(sources:%.c=%.s)

ifneq ($(shell which sudo), )
    sudo := sudo
endif

all:$(all)

$(all):%: %.c
	$(CC) $(CFLAGS) -c -o $@ $<;\
	$(sudo) chmod +x $@


asm:$(asm)

$(asm):%.s: %.c
	$(CC) $(CFLAGS) -S -o $@ $<

clean:
	-rm -f *.s $(all)

.PHONY: all asm clean
