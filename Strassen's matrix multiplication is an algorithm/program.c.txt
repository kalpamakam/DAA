#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix
int** allocateMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

// Function to deallocate memory for a matrix
void deallocateMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to add two matrices
void matrixAdd(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void matrixSubtract(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Function to perform standard matrix multiplication
void standardMatrixMultiply(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to multiply two matrices using Strassen's algorithm
void strassenMatrixMultiply(int** A, int** B, int** C, int n) {
    if (n <= 64) {
        // If the matrix size is small, use standard matrix multiplication
        standardMatrixMultiply(A, B, C, n);
        return;
    }

    // Split matrices into quadrants
    int newSize = n / 2;
    int** A11 = allocateMatrix(newSize, newSize);
    int** A12 = allocateMatrix(newSize, newSize);
    int** A21 = allocateMatrix(newSize, newSize);
    int** A22 = allocateMatrix(newSize, newSize);
    int** B11 = allocateMatrix(newSize, newSize);
    int** B12 = allocateMatrix(newSize, newSize);
    int** B21 = allocateMatrix(newSize, newSize);
    int** B22 = allocateMatrix(newSize, newSize);
    int** C11 = allocateMatrix(newSize, newSize);
    int** C12 = allocateMatrix(newSize, newSize);
    int** C21 = allocateMatrix(newSize, newSize);
    int** C22 = allocateMatrix(newSize, newSize);

    // Divide matrices into quadrants
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculate intermediate matrices
    int** M1 = allocateMatrix(newSize, newSize);
    int** M2 = allocateMatrix(newSize, newSize);
    int** M3 = allocateMatrix(newSize, newSize);
    int** M4 = allocateMatrix(newSize, newSize);
    int** M5 = allocateMatrix(newSize, newSize);
    int** M6 = allocateMatrix(newSize, newSize);
    int** M7 = allocateMatrix(newSize, newSize);

    matrixAdd(A11, A22, M1, newSize);
    matrixAdd(B11, B22, M2, newSize);
    matrixAdd(A21, A22, M3, newSize);
    matrixSubtract(B12, B22, M4, newSize);
    matrixSubtract(B21, B11, M5, newSize);
    matrixAdd(A11, A12, M6, newSize);
    matrixSubtract(A21, A11, M7, newSize);

    // Recursively compute the seven products
    strassenMatrixMultiply(M1, M2, C11, newSize);
    strassenMatrixMultiply(M1, M3, C12, newSize);
    strassenMatrixMultiply(M4, M5, C21, newSize);
    strassenMatrixMultiply(M6, M7, C22, newSize);

    // Compute the four quadrants of the result matrix
    matrixAdd(C11, C12, C, newSize);
    matrixAdd(C21, C22, C + newSize, newSize);
    matrixSubtract(C11, C12, C + newSize * 2, newSize);
    matrixSubtract(C21, C22, C + newSize * 3, newSize);

    // Deallocate memory
    deallocateMatrix(A11, newSize);
    deallocateMatrix(A12, newSize);
    deallocateMatrix(A21, newSize);
    deallocateMatrix(A22, newSize);
    deallocateMatrix(B11, newSize);
    deallocateMatrix(B12, newSize);
    deallocateMatrix(B21, newSize);
    deallocateMatrix(B22, newSize);
    deallocateMatrix(C11, newSize);
    deallocateMatrix(C12, newSize);
    deallocateMatrix(C21, newSize);
    deallocateMatrix(C22, newSize);
    deallocateMatrix(M1, newSize);
    deallocateMatrix(M2, newSize);
    deallocateMatrix(M3, newSize);
    deallocateMatrix(M4, newSize);
    deallocateMatrix(M5, newSize);
    deallocateMatrix(M6, newSize);
    deallocateMatrix(M7, newSize);
}

// Function to print a matrix
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 4; // Change this to the desired matrix size

    int** A = allocateMatrix(n, n);
    int** B = allocateMatrix(n, n);
    int** C = allocateMatrix(n, n);

    // Initialize matrices A and B with random values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    printf("Matrix A:\n");
    printMatrix(A, n, n);
    printf("\nMatrix B:\n");
    printMatrix(B, n, n);

    strassenMatrixMultiply(A, B, C, n);

    printf("\nMatrix C (Result of Strassen's Multiplication):\n");
    printMatrix(C, n, n);

    // Deallocate memory
    deallocateMatrix(A, n);
    deallocateMatrix(B, n);
    deallocateMatrix(C, n);

    return 0;
}
