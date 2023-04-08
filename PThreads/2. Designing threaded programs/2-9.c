#include <stdio.h>

#define ARRAY_SIZE 10

typedef int matrix_t[ARRAY_SIZE][ARRAY_SIZE];
matrix_t MA, MB, MC;

/* Routine to multiply a row by a column and place element in the result matrix */

void mult(
    int size,       /* size of the matrix */
    int row,        /* row of result to compute */
    int column,     /* column of result to compute */
    matrix_t MA,    /* input matrix */
    matrix_t MB,    /* input matrix */
    matrix_t MC     /* result matrix */
) {
    int position;

    MC[row][column] = 0;
    
    for(position = 0; position < size; position++) {
        MC[row][column] = MC[row][column] + (MA[row][column] * MB[position][column]);
    }
}

/* Main: allocates matrix, assigns values, computes the results */
int main(void) {
    int size = ARRAY_SIZE, row, column;

    /* Fill inn matrix values */

    /* Process martix, by row, column */
    for(row = 0; row < size; row++) {
        for(column = 0; column < size; column++) {
            mult(size, row, column, MA, MB, MC);
        }
    }

    /* Print matrix */
    printf("MATRIX: The resulting matrix C is:\n");
    for(row = 0; row < size; row++) {
        for (column = 0; column < size; column++) {
            printf("%5d", MC[row][column]);
        }
        printf("\n");
    }
    
    return 0;
}
