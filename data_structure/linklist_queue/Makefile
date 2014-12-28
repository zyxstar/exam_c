CFLAGS=-Wall
LDFLAGS=-lllist

all: libqueue.so libqueue.a

lib%.so: %.c %.h
	gcc -shared -fPIC -o $@ $< $(CFLAGS)

lib%.a: %.o
	ar -cr $@ $^
	ranlib $@

%.o: %.c queue.h
	gcc -c -o $@ $< $(CFLAGS)

install: libqueue.so libqueue.a
	cp queue.h /usr/local/include
	mv $^ /usr/local/lib

clean:
	rm -f *.o *~ *.a
