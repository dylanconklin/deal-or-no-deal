CC = g++
CPPFLAGS = -Wall -std=c++11

deal:	game.o menu.o main.o
	$(CC) -o deal game.o menu.o main.o

game.o:	game.h

menu.o:	menu.h

.PHONY: clean
clean:
	$(info -- cleaning the directory --)
	rm -f *.o
	rm -f *.gch
	rm -f deal
