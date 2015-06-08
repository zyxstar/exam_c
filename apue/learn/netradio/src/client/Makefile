CC     :=  gcc
CFLAGS +=  -I. -I../include

all: client

client: main.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf main.o client testserver
