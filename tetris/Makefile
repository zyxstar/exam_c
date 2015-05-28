CC       :=  gcc
LDFLAGS  +=  -lm
CFLAGS   +=  -I. -I../utils
VPATH    += ../utils

# vpath %.c ../utils
# vpath %.h ../utils

objs  :=  ctrl.o view.o game.o console.o simple_timer.o
all   :=  tetris_single tetris_single2 tetris_double


all: $(all)

$(all):%: $(objs) %.o
	@echo "\033[31m$@ is being linked ......\033[0m"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# will be automatically derived if not use %.h
# dependency header files
%.o: %.c %.h
	@echo "\033[31m$@ is compiling ......\033[0m"
	$(CC) $(CFLAGS) -c -o $@ $<


debug: CFLAGS += -DDEBUG
debug: all

clean:
	-rm -f *~ $(all) *.o *.log


.PHONY: all debug clean push

