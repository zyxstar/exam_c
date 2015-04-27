CFLAGS := -Wall
CFLAGS += -O2

LDFLAGS :=

OBJ-O := stack.o main.o llist.o

all: main hello

hello: hello.c
	gcc -o $@ $^

main: $(OBJ-O)
	gcc -o $@ $^

%.o: %.c llist.h stack.h
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -f *~ $(OBJ-O) main hello
