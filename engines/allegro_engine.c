#include "engines/allegro_engine.h"

AllegroEngine* allegro_engine_new(World w) {
    AllegroEngine* engine = (AllegroEngine*)malloc(sizeof(AllegroEngine));
    engine->w = w;
    engine->display = NULL;
    return engine;
}

void allegro_engine_init(AllegroEngine* engine) {

    assert(al_init());
    engine->display = al_create_display(800, 600);
    assert(engine->display);
    assert(al_init_primitives_addon());
}

void allegro_engine_run(AllegroEngine* engine) {
    
    const int nbmax = 5;
    point2D tabpoint[] =
    {
        { 100, 100, 0 },
        { 100, 150, 0 },
        { 200, 200, 0 },
        { 200, 300, 0 },
        { 100, 500, 0 }
    };

    al_draw_ribbon((float*)tabpoint, // le tableau de points
        sizeof(point2D), // la taille d'une structure
        al_map_rgb_f(1, 0, 0.5),// couleur
        10, // épaisseur du trait
        nbmax); // nombre max de points
    
    al_flip_display();
    al_rest(4.0);
}

void allegro_engine_die(AllegroEngine* engine) {
    al_destroy_display(engine->display);
    free(engine);
}