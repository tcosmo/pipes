#ifndef DEF_NC_ENGINE_H
#define DEF_NC_ENGINE_H

#include <ncurses.h>
#include "world.h"

typedef struct {
    int max_y, max_x;
    int d_y, d_x;
    World w;
} NcursesEngine;

NcursesEngine* ncurses_engine_new(World w);
void ncurses_engine_init(NcursesEngine* engine);
void ncurses_engine_run(NcursesEngine* engine);
void ncurses_engine_die(NcursesEngine* engine);

#endif