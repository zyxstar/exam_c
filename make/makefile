main:main.o a.o b.o
	gcc -o main main.o a.o b.o
main.o:main.c a.h b.h
	   gcc -c main.c
a.o:a.c a.h
	gcc -c a.c
b.o:b.c b.h
	gcc -c b.c
clean:
	rm main main.o a.o b.o
