LDFLAGS := -lllist

all: main load

%: %.c
	gcc -o $@ $< $(LDFLAGS)

lib_shared: libllist.so
	mv $^ /usr/local/lib
	cp llist.h /usr/local/include

lib%.so: %.c
	gcc -o $@ -fpic -shared $<

lib_static: libllist.a
	mv *.a /usr/local/lib
	cp llist.h /usr/local/include

libllist.a: llist.o
	ar -cr $@ $<
	ranlib $@

%.o: %.c
	gcc -o $@ -c $<

clean:
	rm -f *~ *.a *.so *.o a.out main load tmp
