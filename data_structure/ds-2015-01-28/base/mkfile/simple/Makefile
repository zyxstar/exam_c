CFLAGS := -Wall

OBJ-O := main.o
OBJ-O += stack.o
OBJ-O += llist.o

OBJ   := main hello

all: $(OBJ)

main: $(OBJ-O)
	gcc -o $@ $^

hello: hello.c
	gcc -o $@ $<

%.o: %.c llist.h stack.h
	gcc -o $@ $< -c $(CFLAGS)

clean:
	rm -f *.o *~ $(OBJ)
