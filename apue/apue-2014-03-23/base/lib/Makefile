LDFLAGS := -L/usr/local/lib -ladd

OBJ := main

all: $(OBJ)

main: main.o
	gcc -o $@ $^ $(LDFLAGS)

libadd.so: add.c add.h
	gcc -o $@ $< -shared -fPIC

libadd.a: add.o
	ar -cr $@ $^

%.o: %.c add.h
	gcc -c -o $@ $<

#install: libadd.a
install: libadd.so
	cp add.h /usr/local/include
	mv lib* /usr/local/lib
	/sbin/ldconfig

clean:
	rm -f *~ *.o lib* $(OBJ)
