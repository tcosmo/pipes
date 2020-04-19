#include "graphic_engine.h"

void* engine_new(GraphicEngineType engine_type, World w) {
    switch( engine_type ){
        case TTY:
        return tty_engine_new(w);
        break;

        case NCURSES:
        return ncurses_engine_new(w);
        break;

        case ALLEGRO:
        break;
    }
}

void engine_init(void* graphic_engine, GraphicEngineType engine_type) {
    switch( engine_type ){
        case TTY:
        tty_engine_init(graphic_engine);
        break;

        case NCURSES:
        ncurses_engine_init(graphic_engine);
        break;

        case ALLEGRO:
        break;
    }
}

void engine_run(void* graphic_engine, GraphicEngineType engine_type) {
    switch( engine_type ){
        case TTY:
        tty_engine_run(graphic_engine);
        break;

        case NCURSES:
        ncurses_engine_run(graphic_engine);
        break;

        case ALLEGRO:
        break;
    }
}

void engine_die(void* graphic_engine, GraphicEngineType engine_type) {
    switch( engine_type ){
        case TTY:
        tty_engine_die(graphic_engine);
        break;

        case NCURSES:
        ncurses_engine_die(graphic_engine);
        break;

        case ALLEGRO:
        break;
    }
}