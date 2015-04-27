CFLAGS := -Wall
INCLUDE := -I../include

OBJ-O := llist.o stack.o

all: $(OBJ-O)
	cp $^ ../obj

%.o: %.c
	gcc $(INCLUDE) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *~ $(OBJ-O)
