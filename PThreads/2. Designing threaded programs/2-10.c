#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/resource.h>

// Defines
#define ARRAY_SIZE 10

// Data
typedef int matrix_t[ARRAY_SIZE][ARRAY_SIZE];

typedef struct {
    int id;
    int size;
    int row;
    int column;
    matrix_t *MA;
    matrix_t *MB;
    matrix_t *MC;
} matrix_work_order_t;

// Functions
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

void peer_mult(matrix_work_order_t *work_orderp) {
    mult(
        work_orderp->size,
        work_orderp->row,
        work_orderp->column,
        *(work_orderp->MA),
        *(work_orderp->MB),
        *(work_orderp->MC)
    );
    free(work_orderp);
}

// Main
int main(void) {
    int size = ARRAY_SIZE, row, column;
    matrix_t MA, MB, MC;

    matrix_work_order_t *work_orderp;
    pthread_t peer[size * size];

    /* Process Matrix, by row, column */
    for (row = 0; row < size; row++) {
        for (column = 0; column < size; column++) {
            int id = column + row * 10;
            work_orderp = (matrix_work_order_t *)malloc(sizeof(matrix_work_order_t));

            work_orderp->id = id;
            work_orderp->size = size;
            work_orderp->row = row;
            work_orderp->column = column;
            work_orderp->MA = &MA;
            work_orderp->MB = &MB;
            work_orderp->MC = &MC;

            pthread_create(&(peer[id]), NULL, (void *)peer_mult, (void *)work_orderp);
        }
    }

    /* Wait for peers to exit */
    for (int i = 0; i < (size * size); i++) {
        pthread_join(peer[i], NULL);
    }

    return 0;
}