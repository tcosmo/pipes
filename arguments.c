#include "arguments.h"

const char doc[] = "Welcome to the Collatz pipes viewer!";
const char *argp_program_bug_address = "tristan.sterin@mu.ie";
const char *argp_program_version = "version 0.2";

struct argp argp = { options, parse_option, 0, doc };

Arguments default_arguments() {
    Arguments arguments;
    arguments.verbose = false;
    arguments.engine_type = NCURSES; // default to stdout
    return arguments;
}

static error_t parse_option( int key, char *arg, struct argp_state *state ) {
    Arguments* arguments = state->input;

    switch ( key ) {
    case OPTION_VERBOSE:
        arguments->verbose = true;
        break;
    case 'e':
        if( arg == NULL ) 
            break;
        if( !strcmp( arg, "ncurses") )
            arguments->engine_type = NCURSES;
        else if( !strcmp( arg, "allegro") )
            arguments->engine_type = ALLEGRO;
        else
            arguments->engine_type = TTY;        
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

void parse_arguments(int argc, char *argv[], Arguments* arguments) {
    argp_parse( &argp, argc, argv, 0, 0, arguments);
}
