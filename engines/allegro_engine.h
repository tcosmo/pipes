#ifndef DEF_ALLEGRO_ENGINE_H
#define DEF_ALLEGRO_ENGINE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "world.h"

typedef struct {
    float x, y;
    int data;
} Point2D;

typedef enum {
    VOID = 0,
    TURNING,
    HORIZONTAL,
    VERTICAL,
    HALF_CROSS,
    CROSS
} Motif;

int is_one_one( Motif motif );

typedef struct {
    ALLEGRO_DISPLAY* display;
    int screen_w, screen_h;
    int origin_x, origin_y;
    int cell_w, cell_h;
    int pipe_thickness;
    ALLEGRO_COLOR pipe_color;
    World w;
} AllegroEngine;

AllegroEngine* allegro_engine_new(World w);
void allegro_engine_init(AllegroEngine* engine);
void allegro_engine_run(AllegroEngine* engine);
void allegro_engine_die(AllegroEngine* engine);

#endif