CFLAGS := -Wall
INCLUDE := -I../include

OBJ-O := main.o hello.o

all: $(OBJ-O)
	cp $^ ../obj

%.o: %.c
	gcc $(INCLUDE) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *~ $(OBJ-O)
