#include "engines/ncurses_engine.h"

const char* CELL_REPR[4] = {" 0", ".0", " 1", ".1"};
const char* EMPTY_CELL = "  ";

NcursesEngine* ncurses_engine_new(World w) {

    NcursesEngine* engine = (NcursesEngine*) malloc(sizeof(NcursesEngine));
    engine->w = w;

    return engine;
}

void ncurses_engine_init(NcursesEngine* engine) {
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int d_y = (max_y-engine->w.height)/2;
    int d_x = (max_x-3*engine->w.width)/2;//each cell is 3 char long: e.g. ' .0'

    engine->max_y = max_y;
    engine->max_x = max_x;
    engine->d_y = d_y;
    engine->d_x = d_x;
}

const char* cell_to_str(Cell cell) {
    return CELL_REPR[cell_to_cell_type(cell)];
}

void print_world(NcursesEngine* engine) {
    World w = engine->w;
    int dy = engine->d_y;
    int dx = engine->d_x;

    for(int i_col = 0 ; i_col < w.width ; i_col += 1) { 
        int is_scanning = 0;
        for(int i_row = 0 ; i_row < w.height ; i_row += 1) {
            Cell curr = w.cells[i_row][i_col];

            if( i_row == w.col_start[i_col] )
                is_scanning = 1;

            if( i_row >= w.col_start[i_col]+w.col_size[i_col] )
                is_scanning = 0;

            const char* to_print = (is_scanning) ? cell_to_str(curr) 
                                                 : EMPTY_CELL;
            mvprintw(dy+i_row, dx+3*i_col, " %s", to_print);
        }
    }
}

void ncurses_engine_run(NcursesEngine* engine) {

    fprintf(stderr, "%d %d\n", engine->max_y, engine->max_x);
    fprintf(stderr, "%s\n", cell_to_str(engine->w.cells[0][engine->w.width-1]));

    while(1) {
        erase();
        print_world(engine);
        refresh();

        int c = getch();
        if( c == 'q' )
            break;
    }
}

void ncurses_engine_die(NcursesEngine* engine) {
    endwin();
    free(engine);
}