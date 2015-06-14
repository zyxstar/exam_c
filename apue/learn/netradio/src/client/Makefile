CC     := gcc
CFLAGS += -Wall -I. -I../include
VPATH  += ../include

headers = proto.h site_types.h client_conf.h

all: client testserver

client: main.o $(headers)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

testserver:%: %.c $(headers)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf main.o client testserver
