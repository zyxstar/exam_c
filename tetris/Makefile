COMPILER = gcc
IDIR = ../utils
CXXFLAGS += -I$(IDIR)
OBJECTS = ctrl.o view.o game.o utils.o

tetris_single: $(OBJECTS) tetris_single.o
	$(COMPILER) $(CXXFLAGS) $(OBJECTS) tetris_single.o -lm -lpthread -o tetris_single

tetris_double: $(OBJECTS) tetris_double.o
	$(COMPILER) $(CXXFLAGS) $(OBJECTS) tetris_double.o -lm -lpthread -o tetris_double

tetris_single.o: tetris_single.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

tetris_double.o: tetris_double.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

ctrl.o: ctrl.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

view.o: view.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

game.o: game.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

utils.o: $(IDIR)/utils.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

clean_single:
	rm $(OBJECTS) tetris_single.o tetris_single

clean_double:
	rm $(OBJECTS) tetris_double.o tetris_double


