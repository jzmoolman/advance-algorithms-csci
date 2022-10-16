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
    // for ( int i = 0; i < n*n; i++) {
    //     cout << "index = " << i << " value " << *(matrix_ptr)(m+i) << endl;
    // }
    if ( n >= 2) {
        for ( int row = 0; row < result.n; row++) {
            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result.A11 + (row)*(result.n) + (column)) =
                   *(matrix_ptr)(m + (row*n) + (column));
            }
            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result.A12 + row*result.n + (column)) =
                   *(matrix_ptr)(m + (row*n) + (result.n + column));
            }

            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result.A21 + row*result.n + column) = 
                    *(matrix_ptr)(m + result.n*n + (row * n) + column);
                // cout << "n " << n << endl;         
                // cout << "n/2 " << result.n << endl;         
                // cout << "Row start offset " << (result.n) * n << endl;
                // cout << "Row offset " << row * n << endl ; 
                // cout << "Column offset " <<   column << endl;
                // cout << "Offset " << result.n*n + (row * n) + column << endl;
                // cout << "Value " << *(matrix_ptr)(m + result.n*n + (row * n) + column) << endl;
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

matrix_ptr addMatrix(matrix_ptr A, matrix_ptr B, int n) {
    matrix_ptr C = (matrix_ptr)malloc(sizeof(int *)*n*n);
    for (int i = 0; i < n*n; i++) {
        *(matrix_ptr)(C+i) = *(matrix_ptr)(A+i) + *(matrix_ptr)(B+i);
    }
    return C;
}

matrix_ptr subMatrix(matrix_ptr A, matrix_ptr B, int n) {
    matrix_ptr C = (matrix_ptr)malloc(sizeof(int *)*n*n);
    for (int i = 0; i < n*n; i++) {
        *(matrix_ptr)(C+i) = *(matrix_ptr)(A+i) - *(matrix_ptr)(B+i);
    }
    return C;
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
}

void mergeMatrix(matrix_ptr A,int n, matrix_ptr B, int position ) {
    if (position == 11 ) {
        for ( int row = 0; row < n/2; row++) {
            for ( int column = 0; column < n/2; column++) {
                *(matrix_ptr)(A + (row * n) + (column)) = 
                    *(matrix_ptr)(B + (row * n/2) + (column));
            }
        }
    } else if ( position == 12) {
        for ( int row = 0; row < n/2; row++) {
            for ( int columnA = n/2, columnB = 0; columnA < n; columnA++, columnB++ ) {
                *(matrix_ptr)(A + (row * n) + columnA) = 
                    *(matrix_ptr)(B + row*n/2 + columnB);
            }
        }
    } else if ( position == 21) {
        for ( int rowA = n/2, rowB = 0; rowA < n; rowA++, rowB++) {
            for ( int columnA = 0 , columnB = 0; columnA < n/2; columnA++, columnB++ ) {
                *(matrix_ptr)(A + (rowA * n) + columnA) = 
                    *(matrix_ptr)(B + rowB*n/2 + columnB);
            }
        }
    } else if ( position == 22) {
        for ( int rowA = n/2, rowB = 0; rowA < n; rowA++, rowB++) {
            for ( int columnA = n/2 , columnB = 0; columnA < n; columnA++, columnB++ ) {
                *(matrix_ptr)(A + (rowA * n) + columnA) = 
                    *(matrix_ptr)(B + rowB*n/2 + columnB);
            }
        }
    }
}

matrix_ptr squareMatrixMultiplyRecursive(matrix_ptr A, matrix_ptr B, int n) {
    matrix_ptr C = (matrix_ptr)malloc(sizeof(int *)*n*n);
    if ( n == 1 ) {
        *C = *A * (*B);
    } else {
        divmatrix divA = devideMartix(A, n);
        divmatrix divB = devideMartix(B, n);

        printMatrix(divA.A11, divA.n);
        printMatrix(divB.A11, divA.n);
        matrix_ptr C11 = addMatrix(squareMatrixMultiplyRecursive(divA.A11, divB.A11, divA.n), 
                 squareMatrixMultiplyRecursive(divA.A12, divB.A21, divA.n), divA.n);
        mergeMatrix(C,n, C11, 11);
        
        matrix_ptr C12 = addMatrix(squareMatrixMultiplyRecursive(divA.A11, divB.A12, divA.n), 
                 squareMatrixMultiplyRecursive(divA.A12, divB.A22, divA.n), divA.n);

        matrix_ptr C21 = addMatrix(squareMatrixMultiplyRecursive(divA.A21, divB.A11, divA.n), 
                 squareMatrixMultiplyRecursive(divA.A22, divB.A21, divA.n), divA.n);

        matrix_ptr C22 = addMatrix(squareMatrixMultiplyRecursive(divA.A21, divB.A12, divA.n), 
                 squareMatrixMultiplyRecursive(divA.A22, divB.A22, divA.n), divA.n);
        mergeMatrix(C,n, C11, 11);
        mergeMatrix(C,n, C12, 12);
        mergeMatrix(C,n, C21, 21);
        mergeMatrix(C,n, C22, 22);
        printMatrix(C,n);
    }
    return C;
}


matrix_ptr* SS(divmatrix_t divA, divmatrix_t divB) {
    matrix_ptr* C = (matrix_ptr*)(sizeof(int*)*divA.n);  
    *(C+0) = subMatrix(divB.A12, divB.A22,divB.n);
    *(C+1) = addMatrix(divA.A11, divA.A12,divB.n);
    *(C+2) = addMatrix(divA.A21, divA.A22,divB.n);
    *(C+3) = subMatrix(divB.A21, divB.A11,divB.n);
    *(C+4) = subMatrix(divA.A11, divA.A22, divB.n);
    *(C+5) = subMatrix(divB.A11, divB.A22, divB.n);
    *(C+6) = subMatrix(divA.A12, divA.A22, divB.n);
    *(C+7) = subMatrix(divB.A21, divB.A22, divB.n);
    *(C+8) = subMatrix(divA.A11, divA.A21, divB.n);
    *(C+9) = subMatrix(divB.A11, divB.A12, divB.n);
    return C;
}


matrix_ptr squareMatrixMultiplyRecursiveStraus(matrix_ptr A, matrix_ptr B, int n) {
    matrix_ptr C = (matrix_ptr)malloc(sizeof(int *)*n*n);
    if ( n == 2 ) {
        *C = *A * (*B);
    } else {
        divmatrix divA = devideMartix(A, n);
        divmatrix divB = devideMartix(B, n);

        printMatrix(divA.A11, divA.n);
        printMatrix(divB.A11, divA.n);
        matrix_ptr C11 = addMatrix(squareMatrixMultiplyRecursive(divA.A11, divB.A11, divA.n), 
                 squareMatrixMultiplyRecursive(divA.A12, divB.A21, divA.n), divA.n);
        mergeMatrix(C,n, C11, 11);
        
        matrix_ptr C12 = addMatrix(squareMatrixMultiplyRecursive(divA.A11, divB.A12, divA.n), 
                 squareMatrixMultiplyRecursive(divA.A12, divB.A22, divA.n), divA.n);

        matrix_ptr C21 = addMatrix(squareMatrixMultiplyRecursive(divA.A21, divB.A11, divA.n), 
                 squareMatrixMultiplyRecursive(divA.A22, divB.A21, divA.n), divA.n);

        matrix_ptr C22 = addMatrix(squareMatrixMultiplyRecursive(divA.A21, divB.A12, divA.n), 
                 squareMatrixMultiplyRecursive(divA.A22, divB.A22, divA.n), divA.n);
        mergeMatrix(C,n, C11, 11);
        mergeMatrix(C,n, C12, 12);
        mergeMatrix(C,n, C21, 21);
        mergeMatrix(C,n, C22, 22);
        printMatrix(C,n);
    }
    return C;
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

    cout << "squareMultiplyRecursive" << endl;
    matrix_ptr r = squareMatrixMultiplyRecursive(o, o, 4);
    printMatrixByOffset(r, 4);

   return 0;
}
