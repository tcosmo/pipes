#ifndef DEF_ALLEGRO_ENGINE_H
#define DEF_ALLEGRO_ENGINE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "world.h"

#define BLACK al_map_rgb(0,0,0)
#define WHITE al_map_rgb(255,255,255)
#define GREEN al_map_rgb(50,255,50)
#define PINK al_map_rgb(255,44,180)
#define BLUE al_map_rgb(30,44,230)

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
    int is_running;
    ALLEGRO_DISPLAY* display;
    int screen_w, screen_h;
    int origin_x, origin_y;
    int cell_w, cell_h;
    int pipe_thickness;
    ALLEGRO_COLOR pipe_color;
    World w;
    Motif** world_motifs;
    ALLEGRO_FONT* arial72 ;
    ALLEGRO_EVENT_QUEUE *event_queue;
    int cursor_x, cursor_y;
    char* duplicate_border;
} AllegroEngine;

AllegroEngine* allegro_engine_new(World w);
void allegro_engine_init(AllegroEngine* engine);
void allegro_engine_run(AllegroEngine* engine);
void allegro_engine_die(AllegroEngine* engine);

#endif