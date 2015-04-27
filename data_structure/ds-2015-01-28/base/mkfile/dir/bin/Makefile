all: main hello
	cp $^ ..

main: main.o llist.o stack.o
	gcc -o $@ $^

clean:
	rm -f *~ *.o main hello
