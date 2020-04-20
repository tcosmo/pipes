#ifndef DEF_COLLATZ_H
#define DEF_COLLATZ_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "world.h"

int T(int x);
int is_valid_CS(int* CS, int cs_len);

int* to_base_lil_endian(int x, int b, int* nb_gbit);
CellType* int_to_3p(int x, int* b3p_legnth);
CellType* chars_to_3p(const char* chars);

#endif