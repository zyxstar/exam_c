COMPILER = gcc
IDIR = ../utils
CXXFLAGS += -I$(IDIR)
OBJECTS = user.o train.o menu.o list.o utils.o

app: $(OBJECTS) app.o
	$(COMPILER) $(CXXFLAGS) $(OBJECTS) app.o -o app

app.o: app.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

train.o: train.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

user.o: user.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

menu.o: $(IDIR)/menu.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

list.o: $(IDIR)/list.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

utils.o: $(IDIR)/utils.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

clean:
	rm $(OBJECTS) app.o app



