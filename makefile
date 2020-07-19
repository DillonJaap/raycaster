CFILES=$(wildcard src/main/*.c)\
	   	$(wildcard src/logic/*.c)\
	   	$(wildcard src/objects/*.c)\
	   	$(wildcard src/error/*.c)\


obj=$(CFILES:.c=.o)

CFLAGS=-I./src/main/ -I./src/objects/ -I./src/logic/ -I./src/error/ -I/usr/include/SDL2\
	   $(sdl2-config --libs --cflags) -lSDL2 -lSDL2_ttf -lm -g
CC=gcc

pong: $(obj)
		$(CC) -o $@ $^ $(CFLAGS)

