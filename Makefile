CC=gcc
LIBS=-lncurses
INC=$(shell pwd)

main: world.c graphic_engine.c engines/*.c main.c 
	$(CC) -o build/a.out world.c graphic_engine.c engines/*.c main.c $(LIBS) -I ${INC}
tests: world.c graphic_engine.c engines/*.c tests.c
	$(CC) -o build/tests.out world.c graphic_engine.c engines/*.c tests.c $(LIBS) -I ${INC}
	./build/tests.out