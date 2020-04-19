#include "engines/tty_engine.h"

TTYEngine* tty_engine_new(World w) {

    TTYEngine* engine = (TTYEngine*) malloc(sizeof(TTYEngine));
    engine->w = w;
    return engine;
}

void tty_engine_init(TTYEngine* engine) {
    return;
}

void tty_engine_run(TTYEngine* engine) {
    for(int y = 0 ; y < engine->w.height ; y += 1) {
        for(int x = 0 ; x < engine->w.width ; x += 1)
            printf("%d", cell_to_cell_type(engine->w.cells[y][x]));
        printf("\n");
    }
}

void tty_engine_die(TTYEngine* engine) {
    free(engine);
}