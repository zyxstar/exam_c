CFLAGS  := -DDEBUG
LDFLAGS := -lpthread

INCLUDE := -I.

OBJ := server client

all: $(OBJ)

server: server.o
	gcc -o $@ $^ $(LDFLAGS)

client: client.o
	gcc -o $@ $^ -lcrypt $(LDFLAGS)

%.o: %.c
	gcc $(INCLUDE) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *~ $(OBJ) *.o
