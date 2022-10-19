#include <iostream>

using namespace std;

#define MATRIX_SIZE 3

 typedef int* matrix_ptr;
 typedef struct divmatrix  {
    int n;
    matrix_ptr _11;
    matrix_ptr _12;
    matrix_ptr _21;
    matrix_ptr _22;
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
    result._11 = (matrix_ptr)malloc(sizeof(int *)*result.n*result.n);
    result._12 = (matrix_ptr)malloc(sizeof(int *)*result.n*result.n);
    result._21 = (matrix_ptr)malloc(sizeof(int *)*result.n*result.n);
    result._22 = (matrix_ptr)malloc(sizeof(int *)*result.n*result.n);
    if ( n >= 2) {
        for ( int row = 0; row < result.n; row++) {
            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result._11 + (row)*(result.n) + (column)) =
                   *(matrix_ptr)(m + (row*n) + (column));
            }
            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result._12 + row*result.n + (column)) =
                   *(matrix_ptr)(m + (row*n) + (result.n + column));
            }

            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result._21 + row*result.n + column) = 
                    *(matrix_ptr)(m + result.n*n + (row * n) + column);
            }
            for ( int column = 0; column < result.n; column++) {
                *(matrix_ptr)(result._22 + row*result.n + column) = 
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

        matrix_ptr C11 = addMatrix(squareMatrixMultiplyRecursive(divA._11, divB._11, divA.n), 
                 squareMatrixMultiplyRecursive(divA._12, divB._21, divA.n), divA.n);
        mergeMatrix(C,n, C11, 11);
        
        matrix_ptr C12 = addMatrix(squareMatrixMultiplyRecursive(divA._11, divB._12, divA.n), 
                 squareMatrixMultiplyRecursive(divA._12, divB._22, divA.n), divA.n);

        matrix_ptr C21 = addMatrix(squareMatrixMultiplyRecursive(divA._21, divB._11, divA.n), 
                 squareMatrixMultiplyRecursive(divA._22, divB._21, divA.n), divA.n);

        matrix_ptr C22 = addMatrix(squareMatrixMultiplyRecursive(divA._21, divB._12, divA.n), 
                 squareMatrixMultiplyRecursive(divA._22, divB._22, divA.n), divA.n);
        mergeMatrix(C,n, C11, 11);
        mergeMatrix(C,n, C12, 12);
        mergeMatrix(C,n, C21, 21);
        mergeMatrix(C,n, C22, 22);
    }
    return C;
}


matrix_ptr* SS(divmatrix_t divA, divmatrix_t divB) {
    matrix_ptr* S = (matrix_ptr*)malloc(sizeof(matrix_ptr)*10);  
    *(S+0) = subMatrix(divB._12, divB._22,divB.n);
    *(S+1) = addMatrix(divA._11, divA._12,divB.n);
    *(S+2) = addMatrix(divA._21, divA._22,divB.n);
    *(S+3) = subMatrix(divB._21, divB._11,divB.n);
    *(S+4) = addMatrix(divA._11, divA._22, divB.n);
    *(S+5) = addMatrix(divB._11, divB._22, divB.n);
    *(S+6) = subMatrix(divA._12, divA._22, divB.n);
    *(S+7) = addMatrix(divB._21, divB._22, divB.n);
    *(S+8) = subMatrix(divA._11, divA._21, divB.n);
    *(S+9) = addMatrix(divB._11, divB._12, divB.n);
    return S;
}


matrix_ptr squareMatrixMultiplyRecursiveStrassen(matrix_ptr A, matrix_ptr B, int n) {
    matrix_ptr C = (matrix_ptr)malloc(sizeof(int *)*n*n);
    if ( n == 1 ) {
        *C = *A * (*B);
    } else {
        divmatrix divA = devideMartix(A, n);
        divmatrix divB = devideMartix(B, n);
        matrix_ptr* S = SS(divA, divB);
        matrix_ptr* P = (matrix_ptr*)malloc(sizeof(matrix_ptr)*7);  
        *(P+0) = squareMatrixMultiplyRecursiveStrassen(divA._11, *(S+0), divA.n);
        *(P+1) = squareMatrixMultiplyRecursiveStrassen(divB._22, *(S+1), divA.n);
        *(P+2) = squareMatrixMultiplyRecursiveStrassen(divB._11, *(S+2), divA.n);
        *(P+3) = squareMatrixMultiplyRecursiveStrassen(divA._22, *(S+3), divA.n);
        *(P+4) = squareMatrixMultiplyRecursiveStrassen(*(S+4), *(S+5), divA.n);
        *(P+5) = squareMatrixMultiplyRecursiveStrassen(*(S+6), *(S+7), divA.n);
        *(P+6) = squareMatrixMultiplyRecursiveStrassen(*(S+8), *(S+9), divA.n);


        matrix_ptr C11 = 
            addMatrix(*(P+4), *(P+3), divA.n);
        C11 = subMatrix(C11, *(P+1), divA.n);   
        C11 = addMatrix(C11, *(P+5), divA.n);   

        matrix_ptr C12 = addMatrix(*(P+0), *(P+1), divA.n);
        matrix_ptr C21 = addMatrix(*(P+2), *(P+3), divA.n);
        
        matrix_ptr C22 = addMatrix(*(P+4), *(P+0), divA.n);
        C22 = subMatrix(C22, *(P+2), divA.n);   
        C22 = subMatrix(C22, *(P+6), divA.n);   

        mergeMatrix(C,n, C11, 11);
        mergeMatrix(C,n, C11, 11);
        mergeMatrix(C,n, C12, 12);
        mergeMatrix(C,n, C21, 21);
        mergeMatrix(C,n, C22, 22);
    }
    return C;
}

int main() {
    cout << "Project 1: Advance Algorithms" << endl;
    
    cout << "squareMultiplyRecursive" << endl;
    matrix_ptr o = createMatrix(4);
    matrix_ptr r = squareMatrixMultiplyRecursive(o, o, 4);
    printMatrix(r, 4);

    cout << "squareMultiplyRecursiveStrassen" << endl;
    matrix_ptr s = squareMatrixMultiplyRecursive(o, o, 4);
    printMatrix(s, 4);

    cout << "squareMultiplyRecursiveStrassen - Book" << endl;
    matrix_ptr A = createMatrix(2);
    *A = 1;
    *(A+1) = 3;
    *(A+2) = 7;
    *(A+3) = 5;
    matrix_ptr B = createMatrix(2);
    *B = 6;
    *(B+1) = 8;
    *(B+2) = 4;
    *(B+3) = 2;
    matrix_ptr q = squareMatrixMultiplyRecursiveStrassen(A, B, 2);
    printMatrix(q, 2);
   return 0;
}
