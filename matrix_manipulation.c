#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

// Function to add two matrices
void add_matrices(int m1[SIZE][SIZE], int m2[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

// Function to multiply two matrices
void multiply_matrices(int m1[SIZE][SIZE], int m2[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;  // Initialize the result matrix with 0
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

// Function to transpose a matrix
void transpose_matrix(int m[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[j][i] = m[i][j];  // Swap the rows and columns
        }
    }
}

// Function to print a matrix
void print_matrix(int m[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%4d ", m[i][j]);  // Print each element of the matrix
        }
        printf("\n");
    }
}

int main() {
    int m1[SIZE][SIZE] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };

    int m2[SIZE][SIZE] = {
        {25, 24, 23, 22, 21},
        {20, 19, 18, 17, 16},
        {15, 14, 13, 12, 11},
        {10, 9, 8, 7, 6},
        {5, 4, 3, 2, 1}
    };

    int result[SIZE][SIZE];  // Store result of matrix operations

    printf("Matrix 1:\n");
    print_matrix(m1);

    printf("\nMatrix 2:\n");
    print_matrix(m2);

    add_matrices(m1, m2, result);
    printf("\nMatrix Addition Result:\n");
    print_matrix(result);

    multiply_matrices(m1, m2, result);
    printf("\nMatrix Multiplication Result:\n");
    print_matrix(result);

    transpose_matrix(m1, result);
    printf("\nTranspose of Matrix 1:\n");
    print_matrix(result);

    transpose_matrix(m2, result);
    printf("\nTranspose of Matrix 2:\n");
    print_matrix(result);

    return 0;
}
