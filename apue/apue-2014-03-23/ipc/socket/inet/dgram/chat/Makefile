CFLAGS  := -Wall

OBJ := server client

all: $(OBJ)

client: client.c
	gcc -o $@ $< -lcrypt

server: server.o db.o
	gcc -o $@ $^ -lpthread

%.o: %.c %.h
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -f *~ *.o $(OBJ)
