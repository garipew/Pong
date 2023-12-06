pong: pong.o main.o
	gcc pong.o main.o -o pong -lcurses

pong.o: pong.h pong.c
	gcc -c pong.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.o pong
