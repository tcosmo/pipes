#include "world.h"
#include "graphic_engine.h"

const int GRAPHIC_ENGINE = TTY;

int main() {
    World w = new_world(42,42);
    
    CellType col0[8] = {ONE_CARRY, ZERO, ZERO_CARRY, ZERO_CARRY, ZERO_CARRY, ZERO, ONE, ONE_CARRY};
    init_world(w, col0, 8);
    run_world(w);

    void* graphic_engine = engine_new(GRAPHIC_ENGINE, w);
    engine_init(graphic_engine,GRAPHIC_ENGINE);
    engine_run(graphic_engine,GRAPHIC_ENGINE);
    engine_die(graphic_engine,GRAPHIC_ENGINE);

    free_world(w);
}


































