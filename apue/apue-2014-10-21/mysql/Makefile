CFLAGS   := $(shell mysql_config --cflags)
LDFLAGS  := $(shell mysql_config --libs)

%: %.c
	gcc -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *~ *.o
