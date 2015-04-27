CFLAGS := -Wall
CFLAGS += -O2

LDFLAGS :=

OBJ-O := stack.o main.o llist.o

main: $(OBJ-O)
	gcc -o $@ $^

%.o: %.c llist.h stack.h
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -f *~ $(OBJ-O) main
