object = single_player.o tetris.o view.o game.o utils.o
single_player: $(object)
	gcc -o single_player $(object)
single_player.o: single_player.c tetris.h
	gcc -c single_player.c
tetris.o: tetris.c tetris.h
	gcc -c tetris.c
view.o: view.c view.h utils.h
	gcc -I ../utils -c view.c
game.o: game.c game.h utils.h
	gcc -I ../utils -c game.c
utils.o: utils.c utils.h
	gcc -I ../utils -c  ../utils.c

.PHONY:clean
clean:
	rm single_player $(object)


# main:main.o a.o b.o
# 	gcc -o main main.o a.o b.o
# main.o:main.c a.h b.h
# 	   gcc -c main.c
# a.o:a.c a.h
# 	gcc -c a.c
# b.o:b.c b.h
# 	gcc -c b.c
# clean:
# 	rm main main.o a.o b.o
