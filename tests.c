#include "world.h"

void test_valid_column() {

    CellType col[8] = {ONE_CARRY,ZERO,ZERO_CARRY,ZERO_CARRY,ZERO_CARRY,ZERO,ONE,ONE_CARRY};
    CellType col2[9] = {ONE_CARRY,ONE,ONE,ONE,ONE_CARRY,ZERO,ZERO,ONE_CARRY,ONE_CARRY};
    
    CellType col3[4] = {ONE,ZERO,ONE_CARRY,ONE_CARRY};
    CellType col4[7] = {ZERO_CARRY,ZERO_CARRY,ZERO,ZERO_CARRY,ZERO_CARRY,ONE,ZERO_CARRY};

    CellType col5[3] = {ONE_CARRY,ONE_CARRY,ZERO};
    CellType col6[3] = {ONE,ONE,ONE};

    assert(valid_column(col, 8));
    assert(valid_column(col2,9));
    assert(!valid_column(col3,4));
    assert(!valid_column(col4,7));
    assert(!valid_column(col5,3));
    assert(!valid_column(col6,3));
}

int main() {
    test_valid_column();
}