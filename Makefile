CC=gcc
LIBS=-lm -lncurses
LIBS_ALLEGRO=-lallegro -lallegro_primitives -lallegro_font -lallegro_image -lallegro_ttf -lallegro_dialog
FILES=arguments.c world.c collatz.c graphic_engine.c engines/*.c 
INC=$(shell pwd)

main: $(FILES) main.c
	$(CC) -o build/a.out $(FILES) $(LIBS) $(LIBS_ALLEGRO) main.c -I ${INC}
tests: $(FILES) tests.c
	$(CC) -o $(FILES) tests.c $(LIBS) $(LIBS_ALLEGRO) -I ${INC}
	./build/tests.out