all: hello main
	cp $^ ../bin

hello: hello.o
	gcc -o $@ $^

main: main.o llist.o stack.o
	gcc -o $@ $^

clean:
	rm -f *.o hello main
