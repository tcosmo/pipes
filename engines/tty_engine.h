#ifndef DEF_TTY_ENGINE_H
#define DEF_TTY_ENGINE_H

#include "graphic_engine.h"

typedef struct {
    World w;
} TTYEngine;

TTYEngine* tty_engine_new(World w);
void tty_engine_init(TTYEngine* engine);
void tty_engine_run(TTYEngine* engine);
void tty_engine_die(TTYEngine* engine);

#endif