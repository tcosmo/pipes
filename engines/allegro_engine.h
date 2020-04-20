#ifndef DEF_ALLEGRO_ENGINE_H
#define DEF_ALLEGRO_ENGINE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "world.h"

typedef struct {
    float x, y;
    int data;
} point2D;

typedef struct {
    ALLEGRO_DISPLAY* display;
    World w;
} AllegroEngine;

AllegroEngine* allegro_engine_new(World w);
void allegro_engine_init(AllegroEngine* engine);
void allegro_engine_run(AllegroEngine* engine);
void allegro_engine_die(AllegroEngine* engine);

#endif