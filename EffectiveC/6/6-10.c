#include <stdio.h>
#include <stdlib.h>

int *matrix_sum(
    int rows, 
    int columns,
    int matrix_1[rows][columns], 
    int matrix_2[rows][columns]
    ) {
        int *result_matrix = (int *)calloc(rows * columns, sizeof(int));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result_matrix[i * columns + j] = matrix_1[i][j] + matrix_2[i][j];
            }
        }
    return result_matrix;
}

void print_matrix(int rows, int columns, int arr[rows][columns]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d, ", arr[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int rows = 3;
    int columns = 2;
    int matrix_1[][2] = { 1, 2, 3, 4, 5, 6 };
    int matrix_2[][2] = { 10, 20, 30, 40, 50, 60 };
    int *result_matrix = matrix_sum(rows, columns, matrix_1, matrix_2);
    print_matrix(rows, columns, result_matrix);
}