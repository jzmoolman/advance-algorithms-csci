#include <iostream>
#include <time.h>
#include <stdlib.h>


using namespace std;

const int SIZE = 10;
int k = 10;

void generateArray(int A[]) {
    srand(time(NULL));
    int n;
    for ( int i = 0; i < SIZE; i++) {
        n = rand() % k + 1;
        A[i] =  n;
    }
}

void countingSort(int A[], int B[], int k) {
    int C[k+1];
    for ( int i = 0; i <= k; i++) {
        C[i] = 0;
    }

    for ( int j = 0; j < SIZE ; j++) {
        C[A[j]] = C[A[j]] +1;
    }

    for ( int i = 1; i <= k; i++) {
        C[i] = C[i] + C[i-1];
    }

    for ( int j = SIZE-1; j >= 0; j--) {
        B[C[A[j]]] = A[j];
        C[A[j]] = C[A[j]] -1;
    }

}

void printArray(int A[]) {
    for ( int i = 1 ; i < SIZE; i++) {
        cout << A[i] << ", ";
    }
    cout << endl;
}


int main() {
    cout << "Example of Counting Sort" << endl;
    int A[SIZE+1];
    int B[SIZE+1]; 
    generateArray(A);
    printArray(A);
    countingSort(A,B,SIZE);
    printArray(B);
}