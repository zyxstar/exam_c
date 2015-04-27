# exprot CFLAGS=-DDEBUG

DIRS=lib app

all:
%:
	for dir in $(DIRS) ; do \
		make -C $$dir $@ ; \
	done
	gcc -o main main.o llist.o

clean:
	for dir in $(DIRS) ; do \
		make -C $$dir $@ ; \
	done
	rm -f *~ *.o main hello
