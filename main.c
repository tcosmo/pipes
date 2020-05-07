#include "arguments.h"
#include "world.h"
#include "graphic_engine.h"
#include "collatz.h"

const char* TWO_P_40 = "10330010000323003323333231";
const char* TWO_P_60 = "32300102233333031103222330232223323101";
const char* TWO_P_78 = "10310033010333333102333111002331011101011100310101";
const char* INPUT_COL = "33";//"333333333333333";//"10310231023223";//"322323222222311003331003";

int main( int argc, char *argv[] ) {
    Arguments arguments = default_arguments();
    parse_arguments(argc, argv, &arguments);

    const GraphicEngineType GRAPHIC_ENGINE = arguments.engine_type;//arguments.engine_type;
    const int VERBOSE = arguments.verbose;

    if( VERBOSE )
        fprintf(stderr, "Let's get rolling..\n");
    World w = new_world(15,15);

    int col0_length = strlen(INPUT_COL);
    CellType* col0 = chars_to_3p(INPUT_COL);

    //init_world(w, col0, col0_length);
    //run_world(w);

    if( col0_length < 19 ) // In order not to overflow, 3**19 < 2**31
        assert(check_world(w,VERBOSE));//Checking that the world corresponds to a valid CS

    void* graphic_engine = engine_new(GRAPHIC_ENGINE, w);

    engine_init(graphic_engine,GRAPHIC_ENGINE);
    engine_run(graphic_engine,GRAPHIC_ENGINE);
    engine_die(graphic_engine,GRAPHIC_ENGINE);

    free_world(w);
    free(col0);
}


































