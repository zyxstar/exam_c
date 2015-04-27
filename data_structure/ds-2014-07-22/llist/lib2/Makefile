OBJ-LIB := libllist.so

all: main

main: main.c
	gcc -o main main.c -lllist

libllist.a: llist.o
	ar -cr libllist.a llist.o
	ranlib libllist.a

libllist.so: llist.c
	gcc -fpic -shared -o libllist.so llist.c

%.o: %.c %.h
	gcc -c $<

install: $(OBJ-LIB)
	mv $^ /usr/local/lib
	cp llist.h /usr/local/include

clean:
	rm -f *~ *.o main
