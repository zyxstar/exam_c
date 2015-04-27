all: server client

server: server.c comm.h protocol.h
	gcc -o $@ $< -Wall

client: client.c comm.h	protocol.h
	gcc -o $@ $< -Wall -lcrypt

clean:
	rm -f *~ server client tmp*
