CC       :=  gcc
LDFLAGS  :=  -lm
INCLUDE  :=  -I. -I../utils

vpath %.c ../utils

OBJS  =  ctrl.o view.o game.o console.o simple_timer.o
ALL   =  tetris_single tetris_single2 tetris_double

.PHONY: all debug clean

all: $(ALL)

$(ALL):%: $(OBJS) %.o
	@echo "\033[31m$@ is being linked ......\033[0m"
	$(CC) -o $@ $^ $(INCLUDE) $(LDFLAGS)

%.o: %.c
	@echo "\033[31m$@ is compiling ......\033[0m"
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<


debug: CFLAGS += -DDEBUG
debug: all

clean:
	-rm -f *~ $(ALL) *.o *.log


