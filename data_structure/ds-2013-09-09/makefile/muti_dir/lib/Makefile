CFLAGS := -O2
INCLUDE := -I../include/

all: llist.o
	cp $^ ..

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS) $(INCLUDE)

clean:
	rm -f *~ *.o hello
