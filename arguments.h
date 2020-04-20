#ifndef DEF_ARGS_H
#define DEF_ARGS_H

#include <argp.h>
#include "graphic_engine.h"

enum options_with_no_short_option {
    OPTION_VERBOSE = 0x100, 
};

static struct argp_option options[] = {
    { "verbose", OPTION_VERBOSE, 0, 0, "Enable verbose logging" },
    { "engine", 'e', "ENGINE", 0, "Choosing the graphic engine: `tty`, `ncurses` (default) or `allegro`" },
    { 0 }
};

typedef struct {
    bool verbose;
    GraphicEngineType engine_type;
} Arguments;

Arguments default_arguments();
void parse_arguments(int argc, char *argv[], Arguments* arguments);
static error_t parse_option( int key, char *arg, struct argp_state *state );

#endif