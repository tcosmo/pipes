#ifndef DEF_G_ENGINE_H
#define DEF_G_ENGINE_H

#include "world.h"
#include "engines/tty_engine.h"
#include "engines/ncurses_engine.h"

typedef enum {
    TTY = 0,
    NCURSES,
    ALLEGRO
} GraphicEngineType;

void* engine_new(GraphicEngineType engine_type, World w);
void engine_init(void* graphic_engine, GraphicEngineType engine_type);
void engine_run(void* graphic_engine, GraphicEngineType engine_type);
void engine_die(void* graphic_engine, GraphicEngineType engine_type);

#endif