#include "world.h"
#include "collatz.h"

void test_base_3(int x) {
    int n_trit = 0;
    int* b3 = to_base_lil_endian(x,3,&n_trit);
    int y = 0;
    for( int i = 0 ; i < n_trit ; i += 1 ) {
        printf("%d", b3[n_trit-i-1]);
        y += b3[i]*pow(3,i);
    }
    printf("\n");
    assert(x==y);
    free(b3);
}


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

    printf("base 3 conversion: \n");
    printf("45: "); test_base_3(45);
    printf("83: "); test_base_3(83);
    printf("423: "); test_base_3(423);
}