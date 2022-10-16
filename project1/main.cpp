#include <iostream>

using namespace std;

#define MATRIX_SIZE 3

 typedef int* matrix_t;

matrix_t createMatrix(int id, int n) {
    matrix_t result = (matrix_t)malloc(sizeof(int *)*n*n);
    for ( int row = 1; row <= n; row++) {
        for ( int column = 1; column <= n; column++) {
            *(matrix_t)(result + (row-1)*(n*sizeof(int)) + (column-1)) = id*100+row*10+column;
        }
    }
    return result;
}

void printMatrix(matrix_t m, int n) {
    cout << "[" << endl;
    for ( int row = 1; row <= n; row++) {
        cout << "[";
        for ( int column = 1; column <= n; column++) {
            cout << *(matrix_t)(m + (row - 1)*(n*sizeof(int)) + column-1);
            if (column != n) cout << ", " ;
        }
        cout << "]" << endl;
    }
    cout << "]"  << endl;
}


int main() {
    cout << "Project 1: Advance Algorithms" << endl;
    matrix_t m = createMatrix(1,MATRIX_SIZE);
    printMatrix(m,MATRIX_SIZE);
    matrix_t n = createMatrix(2,MATRIX_SIZE);
    printMatrix(n,MATRIX_SIZE);
   return 0;
}
