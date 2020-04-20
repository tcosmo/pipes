#include "collatz.h"

int T(int x) {
    return (x%2) ? (3*x+1)/2 : x/2;
}

int is_valid_CS(int* CS, int cs_len) {
    for( int i = 1 ; i < cs_len ; i += 1 ) {
        if( CS[i] != T(CS[i-1]) )
            return 0;
    }
    return 1;
}

int* to_base_lil_endian(int x, int b, int* nb_gbit) {
    *nb_gbit = 0;
    int y = x;
    while( y ) {
        y /= b;
        *nb_gbit += 1;
    }
    int* base_b = calloc(*nb_gbit, sizeof(int));
    y = x;
    int k = 0;
    while ( y ) {
        base_b[k] = y%b;
        y /= b;
        k += 1;
    }
    return base_b;
}

void reverse_ct_array(CellType* a, int array_length) {
    CellType b[array_length];
    memcpy(b,a,array_length*sizeof(CellType));

    for( int i = 0 ; i < array_length ; i += 1 ) {
        a[array_length-i-1] = b[i];
    }
}

CellType* int_to_3p(int x, int* b3p_legnth) {

    int n_trit = 0;
    int* b3 = to_base_lil_endian(x,3,&n_trit);
    *b3p_legnth = n_trit;

    CellType* base3p = (CellType*)calloc(n_trit, sizeof(CellType));
    int zero_on = b3[0] == 1;

    for( int i = 0; i < n_trit ; i += 1 ) {
        int trit = b3[i];

        if( trit == 0 ) {
            base3p[i] = ZERO;
            zero_on = 1;
        }
        else if( trit == 1 && zero_on ) {
            base3p[i] = ZERO_CARRY;
        }
        else if( trit == 1 && !zero_on ) {
            base3p[i] = ONE;
        }
        else {
            base3p[i] = ONE_CARRY;
            zero_on = 0;
        }
    }

    reverse_ct_array(base3p, n_trit);
    assert(valid_column(base3p, n_trit));
    free(b3);
    return base3p;
}

CellType* chars_to_3p(const char* chars) {
    int s_len = strlen(chars);
    CellType* base3p = (CellType*) calloc(s_len, sizeof(CellType));
    for( int i = 0 ; i < s_len ; i += 1 ){
        char c = chars[i];
        base3p[i] = (CellType)(c-'0');
    }
    return base3p;
}