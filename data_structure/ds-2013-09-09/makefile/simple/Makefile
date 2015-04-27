CFLAGS := -O2

all: main hello

main: main.o llist.o
	gcc -o $@ $^

hello: hello.o
	gcc -o $@ $^

%.o: %.c llist.h
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -f *~ *.o main hello
