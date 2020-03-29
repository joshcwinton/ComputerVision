// Utilities for working with matrices
// Written by Josh Winton for Computer Vision Homework 4
// Code roughly follows https://www.geeksforgeeks.org/adjoint-inverse-matrix/

#ifndef COMPUTER_VISION_MATRIX_H_
#define COMPUTER_VISION_MATRIX_H_
#define N 3

namespace ComputerVisionProjects
{

// Function to get cofactor of A[p][q] in temp[][]. n is current
// dimension of A[][]
void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n);

// Recursive function for finding determinant of matrix.
// n is current dimension of A[][].
int determinant(int A[N][N], int n);

// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(int A[N][N], int adj[N][N]);

// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(int A[N][N], double inverse[N][N]);

} // namespace ComputerVisionProjects
#endif