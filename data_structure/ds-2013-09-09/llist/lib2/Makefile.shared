LDFLAGS := -lllist

all: main

main: main.c
	gcc -o $@ $< $(LDFLAGS)

lib%.so: %.c %.h
	gcc -shared -fpic -o $@ $<

install: libllist.so
	cp llist.h /usr/local/include
	mv $^ /usr/local/lib
	/sbin/ldconfig

clean:
	rm -f *~ *.o *.a main
