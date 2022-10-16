#include <iostream>

using namespace std;

#define MATRIX_SIZE 3

 typedef int* matrix_ptr;
 typedef struct divmatrix  {
    int n;
    matrix_ptr A11;
    matrix_ptr A12;
    matrix_ptr A21;
    matrix_ptr A22;
 } divmatrix_t;

matrix_ptr createMatrix(int n) {
    matrix_ptr result = (matrix_ptr)malloc(sizeof(int *)*n*n);
    for ( int row = 0; row < n; row++) {
        for ( int column = 0; column < n; column++) {
            *(matrix_ptr)(result + (row * n) + column) = (row+1)*10+column+1;
        }
    }
    return result;
}

divmatrix_t devideMartix(matrix_ptr m, int n){
    divmatrix_t result;
    result.n = n / 2;
    result.A11 = (matrix_ptr)malloc(sizeof(int *)*result.n*result.n);
    result.A12 = (matrix_ptr)malloc(sizeof(int *)*result.n*result.n);
    result.A21 = (matrix_ptr)malloc(sizeof(int *)*result.n*result.n);
    result.A22 = (matrix_ptr)malloc(sizeof(int *)*result.n*result.n);
    for ( int i = 0; i < n*n; i++) {
        cout << "index = " << i << " value " << *(matrix_ptr)(m+i) << endl;
    }
    if ( n >= 2) {
        for ( int row = 0; row < result.n; row++) {
            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result.A11 + (row)*(result.n) + (column)) =
                   *(matrix_ptr)(m + (row) + (column));
            }
            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result.A12 + row*result.n + (column)) =
                   *(matrix_ptr)(m + (row*n) + (result.n + column));
            }

            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result.A21 + row*result.n + column) = 
                    *(matrix_ptr)(m + result.n*n + (row * n) + column);
                cout << "n " << n << endl;         
                cout << "n/2 " << result.n << endl;         
                cout << "Row start offset " << (result.n) * n << endl;
                cout << "Row offset " << row * n << endl ; 
                cout << "Column offset " <<   column << endl;
                cout << "Offset " << result.n*n + (row * n) + column << endl;
                cout << "Value " << *(matrix_ptr)(m + result.n*n + (row * n) + column) << endl;
            }
            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result.A22 + row*result.n + column) = 
                    *(matrix_ptr)(m + result.n*n + row*n + 
                        result.n + column);

            }
        }
    }
    return result;
}

void printMatrixByOffset(matrix_ptr m, int n) {
    for ( int i = 0; i < n*n; i++) {
        cout << "index = " << i << " value " << *(matrix_ptr)(m+i) << endl;
    }
}

void printMatrix(matrix_ptr m, int n) {
    cout << "[" << endl;
    for ( int row = 0; row < n; row++) {
        cout << "[";
        for ( int column = 0; column < n; column++) {
            cout << *(matrix_ptr)(m + (row * n) + column);
            if (column != (n-1)) cout << ", " ;
        }
        cout << "]" << endl;
    }
    cout << "]"  << endl;
    printMatrixByOffset(m,n);
}

matrix_ptr squareMatrixMultipluRecursive(matrix_ptr A, matrix_ptr B, int n) {
    matrix_ptr C = (matrix_ptr)malloc(sizeof(int *)*n*n);
    if ( n == 1 ) {
        *C = *A * (*B);
    } else {
        divmatrix divA = devideMartix(A, n);
        divmatrix divB = devideMartix(B, n);
        matrix_ptr C11 = squareMatrixMultipluRecursive(divA.A11, divB.A11, divA.n) + 
            squareMatrixMultipluRecursive(divA.A12, divB.A21, divA.n);
        matrix_ptr C11 = squareMatrixMultipluRecursive(divA.A11, divB.A12, divA.n);
        matrix_ptr C11 = squareMatrixMultipluRecursive(divA.A12, divB.A22, divA.n);

    } return C;
}


int main() {
    cout << "Project 1: Advance Algorithms" << endl;

    matrix_ptr o = createMatrix(4);
    printMatrix(o,4);
    divmatrix_t tmp = devideMartix(o, 4);
    cout << "A11" << endl;
    printMatrix(tmp.A11, tmp.n);
    cout << "A12" << endl;
    printMatrix(tmp.A12, tmp.n);
    cout << "A21" << endl;
    printMatrix(tmp.A21, tmp.n);
    cout << "A22" << endl;
    printMatrix(tmp.A22, tmp.n);


   return 0;
}
