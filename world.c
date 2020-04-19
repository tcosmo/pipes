#include "world.h"

const int CELL_ACTION[4][2] = {{0,0},{0,1},{1,0},{1,1}};
const CellType ACTION_CELL[2][2] = {{ZERO, ZERO_CARRY}, {ONE, ONE_CARRY}};

World new_world(int height, int width) {
    World w;
    w.height = height;
    w.width = width;

    w.cells = (Cell**) calloc(w.height, sizeof(Cell*));
    for( int y = 0 ; y < w.height ; y += 1)
        w.cells[y] = (Cell*) calloc(w.width, sizeof(Cell));

    w.col_size = (int*) calloc(w.width, sizeof(int));
    w.col_start = (int*) calloc(w.width, sizeof(int));
    return w;
}

void free_world(World w) {
    for( int y = 0 ; y < w.height ; y += 1)
        free(w.cells[y]);
    free(w.cells);
    free(w.col_size);
    free(w.col_start);
}

int valid_column(CellType* column, int column_size) {
    
    int reading_zero_carry = 0;
    int reading_one = 0;
    
    for( int i = 0 ; i < column_size ; i += 1) {
    
        CellType curr = column[i];
        
        if( reading_zero_carry && !(curr == ZERO_CARRY || curr == ZERO) )
            return 0;

        if( reading_one && !(curr == ONE || curr == ONE_CARRY) )
            return 0;

        reading_one = ( curr == ONE );
        reading_zero_carry = ( curr == ZERO_CARRY );
    }

    CellType last = column[column_size-1];
    return last == ZERO_CARRY || last == ONE_CARRY;
}

Cell cell_type_to_cell(CellType ct) {
    Cell c;
    c.bit = CELL_ACTION[ct][0];
    c.carry = CELL_ACTION[ct][1];
    return c;
}

CellType cell_to_cell_type(Cell c) {
    return (CellType) c.carry + 2*c.bit;
}

void init_world(World w, CellType* column, int column_size) {
    assert(column_size <= w.height);
    assert(valid_column(column, column_size));

    for( int y = 0 ; y < column_size ; y+= 1) {
        Cell cell = cell_type_to_cell(column[y]); 
        w.cells[y][w.width-1] = cell;
    }
    w.col_size[w.width-1] = column_size;
    w.col_start[w.width-1] = 0;
}

void run_world(World w) {

    for(int i_col = w.width-2 ; i_col >= 0 ; i_col -= 1) {

        int row_start = w.col_start[i_col+1];
        int row_end = row_start + w.col_size[i_col+1];
        w.col_start[i_col] = row_start;
        int my_end = row_end;

        for(int i_row = row_start ; i_row < row_end ; i_row += 1) {
            assert(i_row+1 < w.height);//We need enough height to look at next row

            Cell* me = &w.cells[i_row][i_col];
            Cell east = w.cells[i_row][i_col+1];
            Cell* south = &w.cells[i_row+1][i_col];

            me->carry = (me->bit + east.bit + east.carry) >= 2;
            south->bit = (me->bit + east.bit + east.carry)%2; 

            if( i_row == row_start && (east.carry+east.bit) == 0 )
                w.col_start[i_col] += 1;
            
            if( i_row == row_end-1 && south->bit == 1) {
                south->carry = 1;
                my_end = row_end+1;
            }
        }
        w.col_size[i_col] = my_end - w.col_start[i_col];
        //fprintf(stderr, "%d\n", w.col_size[i_col]);
    }

}