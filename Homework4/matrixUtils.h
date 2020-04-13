// Utilities for working with matrices
// Written by Josh Winton for Computer Vision Homework 4
// Code roughly follows https://www.geeksforgeeks.org/adjoint-inverse-matrix/

#ifndef COMPUTER_VISION_MATRIX_H_
#define COMPUTER_VISION_MATRIX_H_
#define N 3

#include <array>

using namespace std;

namespace ComputerVisionProjects
{

// Function to get cofactor of A[p][q] in temp[][]. n is current
// dimension of A[][]
void getCofactor(array<array<int, N>, N> &A, array<array<int, N>, N> &temp, int p, int q, int n);

// Recursive function for finding determinant of matrix.
// n is current dimension of A[][].
int determinant(array<array<int, N>, N> A, int n);

// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(array<array<int, N>, N> &A, array<array<int, N>, N> &adj);

// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(array<array<int, N>, N> A, array<array<double, N>, N> &inverse);

// Generic function to display the matrix. We use it to display
// both adjoin and inverse. adjoin is integer matrix and inverse
// is a float.
template <class T>
void display(T A);
} // namespace ComputerVisionProjects
#endif