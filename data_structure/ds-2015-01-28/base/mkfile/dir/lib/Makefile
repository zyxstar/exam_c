CFLAGS  := -Wall
INCLUDE := -I../include

OBJ-O   := stack.o
OBJ-O   += llist.o

all: $(OBJ-O)
	cp *.o ../bin

%.o: %.c
	gcc -o $@ $< -c $(INCLUDE) $(CFLAGS)

clean:
	rm -f *.o *~
