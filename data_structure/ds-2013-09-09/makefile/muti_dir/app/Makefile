CFLAGS := -O2
INCLUDE := -I../include/

all: main.o hello
	cp $^ ..

hello: hello.o
	gcc -o $@ $^

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS) $(INCLUDE)

clean:
	rm -f *~ *.o hello
