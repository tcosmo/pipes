#include "engines/allegro_engine.h"

AllegroEngine* allegro_engine_new(World w) {
    AllegroEngine* engine = (AllegroEngine*)malloc(sizeof(AllegroEngine));
    engine->w = w;
    engine->display = NULL;
    engine->screen_w = 1500;
    engine->screen_h = 900;

    engine->cell_w = 20;
    engine->cell_h = 20;

    engine->origin_x = 250;
    engine->origin_y = 50;

    engine->pipe_thickness = 4;
    engine->pipe_color = al_map_rgb_f(0.4, 0.4, 0.4);

    return engine;
}

void allegro_engine_init(AllegroEngine* engine) {
    assert(al_init());
    engine->display = al_create_display(engine->screen_w, engine->screen_h);
    assert(engine->display);
    assert(al_init_primitives_addon());
}

void wait_for_keypress()
{
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT event;
    
    al_install_keyboard();
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    do
        al_wait_for_event(event_queue, &event);
    while (event.type != ALLEGRO_EVENT_KEY_DOWN);
    
    al_destroy_event_queue(event_queue);
}

int is_one_one( Motif motif ) {
    /* Does the motif corresponds to a .1 ? */
    return motif == HALF_CROSS || motif == CROSS;
}

Point2D* get_motif_points(Motif motif, int* n_points, int o_x, int o_y, int w, int h) {
    Point2D* to_return = NULL;
    int to_return_n_points = 0;
    if( motif == TURNING ) {
        to_return_n_points = 3;
        to_return = calloc(to_return_n_points, sizeof(Point2D));
        Point2D tabpoint[] = {
            { o_x+w, o_y+h/2, 0 },
            { o_x+w/2, o_y+h/2, 0 },
            { o_x+w/2, o_y+h, 0 },
        };
        for( int i = 0 ; i < to_return_n_points ; i += 1 )
            to_return[i] = tabpoint[i];
        memcpy(to_return,tabpoint,sizeof(Point2D)*(to_return_n_points));
    }
    else if ( motif == HORIZONTAL ) {
        to_return_n_points = 2;
        to_return = calloc(to_return_n_points, sizeof(Point2D));
        Point2D tabpoint[] = {
            { o_x+w, o_y+h/2, 0 },
            { o_x, o_y+h/2, 0 },
        }; 
        memcpy(to_return,tabpoint,sizeof(Point2D)*(to_return_n_points));
    } 
    else if ( motif == VERTICAL ) {
        to_return_n_points = 4;
        to_return = calloc(to_return_n_points, sizeof(Point2D));
        Point2D tabpoint[] =
        {
            { o_x+w/2, o_y, 0 },
            { o_x+w/2, o_y+h, 0 },
            { o_x+w/2, o_y+h/2, 0 },
            { o_x, o_y+h/2, 0 },
        };
        memcpy(to_return,tabpoint,sizeof(Point2D)*(to_return_n_points));
    }
    else if ( motif == HALF_CROSS ) {
        to_return_n_points = 4;
        to_return = calloc(to_return_n_points, sizeof(Point2D));
        Point2D tabpoint[] =
        {
            { o_x+w/2, o_y, 0 },
            { o_x+w/2, o_y+h/2, 0 },
            { o_x+w, o_y+h/2, 0 },
            { o_x, o_y+h/2, 0 },
        };
        memcpy(to_return,tabpoint,sizeof(Point2D)*(to_return_n_points));
    }
    else if ( motif == CROSS ) {
        to_return_n_points = 5;
        to_return = calloc(to_return_n_points, sizeof(Point2D));
        Point2D tabpoint[] =
        {
            { o_x+w/2, o_y, 0 },
            { o_x+w/2, o_y+h, 0 },
            { o_x+w/2, o_y+h/2, 0 },
            { o_x+w, o_y+h/2, 0 },
            { o_x, o_y+h/2, 0 },
        };
        memcpy(to_return,tabpoint,sizeof(Point2D)*(to_return_n_points));
    }

    *n_points = to_return_n_points;
    return to_return;
}

void render_motif(AllegroEngine* engine, Motif motif, int o_x, int o_y) {
    int w = engine->cell_h, h = engine->cell_w;
    int n_points;

    Point2D* tabpoint = get_motif_points(motif, &n_points, o_x, o_y, w, h);

    al_draw_ribbon((float*)tabpoint,
        sizeof(Point2D),
        engine->pipe_color,
        engine->pipe_thickness,
        n_points);   
    
    free(tabpoint);
}

void render_cell(AllegroEngine* engine, int i_col, int i_lig) {

    Cell cell = engine->w.cells[i_lig][i_col];
    CellType ct = cell_to_cell_type(cell);

    int bit_below = 0;
    if( i_lig + 1 < engine->w.height )
        bit_below = engine->w.cells[i_lig+1][i_col].bit;

    int cell_origin_x = engine->origin_x + i_col*engine->cell_w;
    int cell_origin_y = engine->origin_y + i_lig*engine->cell_h;

    if( ct == ZERO && !bit_below )
        return;//nothing to render
    else if( ct == ZERO && bit_below )
        render_motif(engine, TURNING, cell_origin_x, cell_origin_y);
    else if( ct == ZERO_CARRY )
        render_motif(engine, HORIZONTAL, cell_origin_x, cell_origin_y);
    else if( ct == ONE )
        render_motif(engine, VERTICAL, cell_origin_x, cell_origin_y);
    else if( ct == ONE_CARRY && !bit_below )
        render_motif(engine, HALF_CROSS, cell_origin_x, cell_origin_y);
    else if( ct == ONE_CARRY && bit_below )
        render_motif(engine, CROSS, cell_origin_x, cell_origin_y);

    return;
}

void allegro_engine_run(AllegroEngine* engine) {
    
    int width = engine->w.width;
    int height = engine->w.height;
    
    ALLEGRO_TRANSFORM t;

    al_identity_transform(&t);
    al_scale_transform(&t, 2, 2);
    //al_use_transform(&t);

    /* 
        Todo: grid, translate, zoom
    */

    for( int i_col = width-1; i_col >= 0 ; i_col -= 1 ) {
        for( int i_lig = 0 ; i_lig < height ; i_lig += 1 ) {
            render_cell(engine,i_col,i_lig);
        }
    }

    
    
    al_flip_display();
    wait_for_keypress();
}

void allegro_engine_die(AllegroEngine* engine) {
    al_destroy_display(engine->display);
    free(engine);
}