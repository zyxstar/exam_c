
lib_static: libqueue.a
	cp queue.h /usr/local/include
	mv $< /usr/local/lib

lib%.a: %.o
	ar -cr $@ $<

%.o: %.c
	gcc -o $@ -c $<
