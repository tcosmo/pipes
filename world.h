#ifndef DEF_WORLD_H
#define DEF_WORLD_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef enum {
    ZERO = 0,
    ZERO_CARRY,
    ONE,
    ONE_CARRY
} CellType;

typedef struct {
    int bit;
    int carry;
} Cell;

Cell cell_type_to_cell(CellType ct);
CellType cell_to_cell_type(Cell c);

typedef struct {
    Cell** cells;
    char** defined;
    unsigned char* border;
    int* col_size;
    int* col_start;
    int height, width;
} World;

World new_world(int height, int width, char* border);
void free_world(World w);

int valid_column(CellType* column, int column_size);
void init_world(World w, CellType* column, int column_size);

void run_world(World w);
int check_world(World w, int print);

int is_position_valid(World w, int x, int y);
void increase_border(World w, int x);

#endif