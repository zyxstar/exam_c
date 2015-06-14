CC      := gcc
CFLAGS  += -I. -I../include -g
LDFLAGS += -lpthread
VPATH   += ../include

headers = proto.h site_types.h server_conf.h
objs    = main.o mytbf.o medialib.o thr_channel.o thr_list.o

all: server

server: $(objs)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

mytbf_test:%: %.c mytbf.o

medialib_test:%: %.c mytbf.o medialib.o

%.o: %.c %.h $(headers)
	$(CC) $(CFLAGS) -c -o $@ $<



clean:
	rm -rf *.o server mytbf_test medialib_test


# -g for gdb
# gdb server
# set args -F
# r


#tcpdump -i eth0 -n -w /tmp/cap0
#for wireshark
