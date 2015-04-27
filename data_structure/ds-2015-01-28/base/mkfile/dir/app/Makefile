CFLAGS  := -Wall
INCLUDE := -I../include

OBJ-O   := main.o

all: $(OBJ-O) hello
	cp $^ ../bin

%.o: %.c
	gcc -o $@ $< -c $(INCLUDE) $(CFLAGS)

clean:
	rm -f *.o *~ hello
