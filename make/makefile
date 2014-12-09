COMPILER = gcc
IDIR = ../utils
CXXFLAGS += -I$(IDIR)
EXEC = main
OBJECTS = main.o a.o b.o utils.o

$(EXEC): $(OBJECTS)
	$(COMPILER) $(CXXFLAGS) $(OBJECTS) -lm -o $(EXEC)

# main:main.o a.o b.o utils.o
# 	gcc main.o a.o b.o utils.o -lm -o main

main.o: main.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@

# main.o: main.c a.h b.h ../utils/utils.h
# 	gcc -I../utils -c main.c

a.o: a.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@
	# gcc -c -lm a.c

b.o: b.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@
	# gcc -c b.c

utils.o: $(IDIR)/utils.c
	$(COMPILER) -c $(CXXFLAGS) $^ -o $@
# utils.o:../utils/utils.c ../utils/utils.h
	# gcc -I../utils -c ../utils/utils.c

clean:
	rm main main.o a.o b.o



# main:main.o a.o b.o
# 	gcc -o main main.o a.o b.o
# main.o:main.c a.h b.h
# 	gcc -c main.c
# a.o:a.c a.h
# 	gcc -c a.c
# b.o:b.c b.h
# 	gcc -c b.c
# clean:
# 	rm main main.o a.o b.o

# make -f Make.Linux
# make --file Make.AIX
