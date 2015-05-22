CC       :=  gcc
INCLUDE  :=  -I. -I../utils

vpath %.c ../utils

OBJS = user.o train.o menu.o list.o console.o

app:%: $(OBJS) %.o
	$(CC) -o $@ $^ $(INCLUDE) $(LDFLAGS)


%o:%c
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<


clean:
	-rm -f *~ *.o *.log app

debug: CFLAGS += -DDEBUG
debug: app

#make -e CFLAGS+=-DDEBUG

