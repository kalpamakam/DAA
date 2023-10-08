Given an N×N chessboard, the task is to place N queens on the board 
so that no two queens can attack each other. The objective of this 
case study is to implement the N-Queens algorithm in C Language to 
find all possible arrangements of the queens on the chessboard.

#include <stdio.h>
#define N 8

int board[N][N];

// Function to check if it's safe to place a queen at board[row][col]
int isSafe(int row, int col) {
    // Check the left side of the row
    for (int i = 0; i < col; i++) {
        if (board[row][i])
            return 0;
    }

    // Check upper diagonal on the left
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return 0;
    }

    // Check lower diagonal on the left
    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j])
            return 0;
    }

    return 1;
}

// Function to solve N-Queens problem using backtracking
int solveNQueens(int col) {
    if (col >= N) {
        // All queens are placed, print the solution
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return 1;
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;
            res = solveNQueens(col + 1) || res;
            board[i][col] = 0; // Backtrack
        }
    }

    return res;
}

int main() {
    if (solveNQueens(0) == 0) {
        printf("No solution exists for N = %d\n", N);
    }
    return 0;
}


