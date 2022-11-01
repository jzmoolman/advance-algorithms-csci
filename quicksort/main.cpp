#include <iostream>
#include <time.h>
#include <stdlib.h>


using namespace std;

const int SIZE = 10;

void generateArray(int A[]) {
    srand(time(NULL));
    int n;
    for ( int i = 0; i < SIZE; i++) {
        while (1) {
            n = rand() % 100 + 1;
            for (int j = 0; j < i; j++) {
                if ( A[j] == n) {
                    continue;
                }

            }
            break;
        }
        A[i] =  n;
    }

}

void partion(int A[], int lo, int hi) {
    int r = A[hi];
    int i = lo-1;

    for ( int j =  lo; j < hi-1; j ++ ) {


    }

}

void quickSort(int A[], int lo, int hi) {




}

void printArray(int A[]) {
    for ( int i = 0 ; i < SIZE; i++) {
        cout << A[i] << ", ";
    }
    cout << endl;
}


int main() {
    cout << "Example of QuickSort" << endl;
    int array[SIZE];
    generateArray(array);
    printArray(array);A
    quickSort(array,0,9)

}