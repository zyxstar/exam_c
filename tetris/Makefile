COMPILER = gcc
IDIR = ../utils
CXXFLAGS += -I$(IDIR)
OBJECTS = ctrl.o view.o game.o console.o simple_timer.o

tetris_single: $(OBJECTS) tetris_single.o
	$(COMPILER) $(CXXFLAGS) $(OBJECTS) tetris_single.o -lm -o tetris_single

tetris_single2: $(OBJECTS) tetris_single2.o
	$(COMPILER) $(CXXFLAGS) $(OBJECTS) tetris_single2.o -lm -o tetris_single2

tetris_double: $(OBJECTS) tetris_double.o
	$(COMPILER) $(CXXFLAGS) $(OBJECTS) tetris_double.o -lm -o tetris_double

tetris_single.o: tetris_single.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

tetris_single2.o: tetris_single2.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

tetris_double.o: tetris_double.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

ctrl.o: ctrl.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

view.o: view.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

game.o: game.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

console.o: $(IDIR)/console.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

simple_timer.o: $(IDIR)/simple_timer.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

clean:
	rm $(OBJECTS) tetris_single.o tetris_single

clean_single2:
	rm $(OBJECTS) tetris_single2.o tetris_single2

clean_double:
	rm $(OBJECTS) tetris_double.o tetris_double


