#include "world.h"
#include "graphic_engine.h"
#include "collatz.h"

const int GRAPHIC_ENGINE = ALLEGRO;
const char* INPUT_COL = "10330010000323003323333231";
const int PRINT_CS = 0;//do we print the underlying CS (to stderr)

int main() {
    World w = new_world(42,42);

    int col0_length = strlen(INPUT_COL);
    CellType* col0 = chars_to_3p(INPUT_COL);

    init_world(w, col0, col0_length);
    run_world(w);

    if( col0_length < 19 ) // In order not to overflow, 3**19 < 2**31
        assert(check_world(w,PRINT_CS));//Checking that the world corresponds to a valid CS

    void* graphic_engine = engine_new(GRAPHIC_ENGINE, w);
    engine_init(graphic_engine,GRAPHIC_ENGINE);
    engine_run(graphic_engine,GRAPHIC_ENGINE);
    engine_die(graphic_engine,GRAPHIC_ENGINE);

    free_world(w);
    free(col0);
}


































