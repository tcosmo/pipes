#include "engines/allegro_engine.h"

AllegroEngine* allegro_engine_new(World w) {
    AllegroEngine* engine = (AllegroEngine*)malloc(sizeof(AllegroEngine));
    engine->is_running = 1;
    engine->w = w;

    engine->cursor_x = 0;
    engine->cursor_y = w.height-1;

    engine->display = NULL;
    engine->screen_w = 1500;
    engine->screen_h = 1000;

    engine->cell_w = 60;
    engine->cell_h = 60;

    int to_draw_width = w.width*engine->cell_w;
    int to_draw_height = w.width*engine->cell_h;
    engine->origin_x = (engine->screen_w  - to_draw_width)/2;
    engine->origin_y = (engine->screen_h  - to_draw_width)/2;

    engine->pipe_thickness = 4;
    engine->pipe_color = al_map_rgb_f(0.4, 0.4, 0.4);

    engine->world_motifs = (Motif**) calloc(w.height, sizeof(Motif*));
    for( int i_row = 0 ; i_row < w.height ; i_row += 1)
        engine->world_motifs[i_row] = (Motif*) calloc(w.width, sizeof(Motif));

    return engine;
}

void allegro_engine_init(AllegroEngine* engine) {
    assert(al_init());
    engine->display = al_create_display(engine->screen_w, engine->screen_h);
    assert(engine->display);
    assert(al_init_image_addon());
    assert(al_init_font_addon());
    assert(al_init_ttf_addon());
    assert(al_init_primitives_addon());
    engine->arial72 = al_load_font("arial.ttf",engine->cell_w ,0);
    assert(engine->arial72);
    assert(al_install_keyboard());
    engine->event_queue = al_create_event_queue();
    assert(engine->event_queue);
    al_register_event_source(engine->event_queue,
        al_get_display_event_source(engine->display));
    al_register_event_source(engine->event_queue,
        al_get_keyboard_event_source());
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

    if(motif == VOID) {
        al_draw_filled_rectangle(o_x, o_y, o_x+w, o_y+h,al_map_rgb_f(0.3, 0, 0.5)
        );
        return;
    }

    Point2D* tabpoint = get_motif_points(motif, &n_points, o_x, o_y, w, h);

    al_draw_ribbon((float*)tabpoint,
        sizeof(Point2D),
        engine->pipe_color,
        engine->pipe_thickness,
        n_points);

    /*if( motif == HALF_CROSS ) {
        al_draw_filled_rectangle(o_x, o_y, o_x+w, o_y+h,
        al_map_rgb_f(0, 0.6, 0.6));
    }
    if( motif == VERTICAL ) {
        al_draw_filled_rectangle(o_x, o_y, o_x+w, o_y+h,
        al_map_rgb_f(0, 0.4, 0.6));
    }
    //al_map_rgb_f(0, 0.6, 0.6)
    if( motif == CROSS ) {
        al_draw_filled_rectangle(o_x, o_y, o_x+w, o_y+h,al_map_rgb_f(1, 0, 0.5)
        );
    }*/
    
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
        engine->world_motifs[i_lig][i_col] = VOID;
    else if( ct == ZERO && bit_below )
        engine->world_motifs[i_lig][i_col] = TURNING;
    else if( ct == ZERO_CARRY )
        engine->world_motifs[i_lig][i_col] = HORIZONTAL;
    else if( ct == ONE )
        engine->world_motifs[i_lig][i_col] = VERTICAL;
    else if( ct == ONE_CARRY && !bit_below )
        engine->world_motifs[i_lig][i_col] = HALF_CROSS;
    else if( ct == ONE_CARRY && bit_below )
        engine->world_motifs[i_lig][i_col] = CROSS;

    int col_start = engine->w.col_start[i_col];
    int col_end = col_start + engine->w.col_size[i_col];

    if( i_lig >= col_start && i_lig < col_end )
        render_motif(engine, engine->world_motifs[i_lig][i_col], cell_origin_x, cell_origin_y);

    return;
}

void count_motifs(AllegroEngine* engine, int print) {

    int counting[engine->w.width][6];
    for( int i_col = 0 ; i_col < engine->w.width ; i_col += 1)
        for( int i_motif = 0 ; i_motif < 6 ; i_motif += 1 )
            counting[i_col][i_motif] = 0;

    for( int i_col = 0 ; i_col < engine->w.width ; i_col += 1 ) {
        int col_start = engine->w.col_start[i_col];
        int col_end = col_start + engine->w.col_size[i_col];

        for( int i_lig = col_start ; i_lig < col_end ; i_lig += 1 ) {
            Motif motif = engine->world_motifs[i_lig][i_col];
            counting[i_col][motif] += 1;
        }
    }

    if(print)
        for(int i_col = 0 ; i_col < engine->w.width ; i_col += 1)
            printf("%d,%d,%d,%d,%d,%d\n", counting[i_col][0], counting[i_col][1], counting[i_col][2], counting[i_col][3], counting[i_col][4], counting[i_col][5]);
}


void render_symbol(AllegroEngine* engine, Cell cell, int o_x, int o_y) {
    char c = '0' + (cell.bit == 1);
    al_draw_textf(engine->arial72, WHITE, o_x, o_y,
                  ALLEGRO_ALIGN_CENTRE, "%c", c);
}

void render_cell_symbol(AllegroEngine* engine, int i_col, int i_lig) {
    Cell cell = engine->w.cells[i_lig][i_col];
    int cell_origin_x = i_col*engine->cell_w;
    int cell_origin_y = i_lig*engine->cell_h;
    render_symbol(engine, cell, cell_origin_x, cell_origin_y);
}

void render_world_symbol(AllegroEngine* engine)
{
    int width = engine->w.width;
    int height = engine->w.height;
    for( int i_col = width-1; i_col >= 0 ; i_col -= 1 ) {
        for( int i_lig = 0 ; i_lig < height ; i_lig += 1 ) {
            if( engine->w.defined[i_lig][i_col] )
                render_cell_symbol(engine,i_col,i_lig);
        }
    }
}

void render_world_grid(AllegroEngine* engine) {
    for( int i_col = 0 ; i_col <= engine->w.width ; i_col += 1)
        al_draw_line(i_col*engine->cell_w, 0, 
                     i_col*engine->cell_w, engine->w.height*engine->cell_h,
                     WHITE, 1);
    for( int i_lig = 0 ; i_lig <= engine->w.height ; i_lig += 1)
        al_draw_line(0, i_lig*engine->cell_h, 
                     engine->w.width*engine->cell_w, i_lig*engine->cell_h, 
                     WHITE, 1);
}

void render_cursor(AllegroEngine* engine) {
    int c_x = engine->cursor_x;
    int c_y = engine->cursor_y;

    al_draw_rectangle(c_x*engine->cell_w, c_y*engine->cell_h, 
                      (c_x+1)*engine->cell_w, (c_y+1)*engine->cell_h, 
                      GREEN, 4);
}

void move_cursor(AllegroEngine* engine, int d_x, int d_y) {
    int new_c_x = engine->cursor_x + d_x;
    int new_c_y = engine->cursor_y + d_y;
    if( !is_position_valid(engine->w, new_c_x, new_c_y) )
        return;
    engine->cursor_x = new_c_x;
    engine->cursor_y = new_c_y;
}

void render_world_border(AllegroEngine* engine) {
    for( int i_col = 0 ; i_col < engine->w.width ; i_col += 1 ) {
        char c = engine->w.border[i_col];
        if( !c ) continue;
        if( c >= 1 )
            al_draw_line((i_col)*engine->cell_w, 
                            (engine->w.height)*engine->cell_h, 
                    (i_col+1)*engine->cell_w, engine->w.height*engine->cell_h,
                    PINK, 5);
        if( c == 2 )
            al_draw_line((i_col+1)*engine->cell_w, 
                            (engine->w.height-1)*engine->cell_h, 
                    (i_col+1)*engine->cell_w, engine->w.height*engine->cell_h,
                    PINK, 5);
    }
}

void allegro_engine_run(AllegroEngine* engine) {
    
    ALLEGRO_TRANSFORM t;
    al_identity_transform(&t);
    al_translate_transform(&t, engine->origin_x, engine->origin_y);
    al_use_transform(&t);

    while( engine->is_running ) {
        al_clear_to_color(BLACK);
        render_world_grid(engine);
        render_cursor(engine);
        render_world_symbol(engine);
        render_world_border(engine);
        al_flip_display();

        ALLEGRO_EVENT event;
        al_wait_for_event(engine->event_queue, &event);

        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_B: 
                    increase_border(engine->w, engine->cursor_x); 
                    break;
            }
        }

        if(event.type == ALLEGRO_EVENT_KEY_CHAR) {
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:    move_cursor(engine, 0, -1); break;
                case ALLEGRO_KEY_RIGHT: move_cursor(engine, 1, 0);  break;
                case ALLEGRO_KEY_DOWN:  move_cursor(engine, 0, 1);  break;
                case ALLEGRO_KEY_LEFT:  move_cursor(engine, -1, 0);  break;
                case ALLEGRO_KEY_ESCAPE: engine->is_running = 0; break;
            }
        }
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            engine->is_running = 0;
        }
    }

}

void allegro_engine_die(AllegroEngine* engine) {
    al_destroy_display(engine->display);
    al_destroy_font(engine->arial72);
     al_destroy_event_queue(engine->event_queue);
    for( int i_row = 0; i_row < engine->w.height ; i_row += 1 )
        free(engine->world_motifs[i_row]);

    free(engine->world_motifs);
    free(engine);
}