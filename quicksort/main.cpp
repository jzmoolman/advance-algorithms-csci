#include <iostream>
#include <time.h>
#include <stdlib.h>


using namespace std;

const int SIZE = 10;

void generateArray(int A[]) {
    srand(time(NULL));
    int n;
    for ( int i = 0; i < SIZE; i++) {
        // while (1) {
            n = rand() % 10 + 1;
            // for (int j = 0; j < i; j++) {
            //     if ( A[j] == n) {
            //         continue;
            //     }

            // }
            //break;
        // }
        A[i] =  n;
    }

}

int partition_sort(int* buffer,int p, int r ) {
  int pvalue = buffer[r];
  int i = p-1;
  for (int j = p; j < r; j++) {
    if ( buffer[j] <= pvalue) {
      i++;
      int tmp = buffer[i];
      buffer[i] = buffer[j];
      buffer[j] = tmp;
    }
  }
  int tmp = buffer[i+1];
  buffer[i+1] = buffer[r];
  buffer[r] = tmp;
  return  i+1;
}

void quick_sort(int *buffer, int p, int r) {
    if (p < r) {
        int q = partition_sort(buffer, p, r);
        printf("p = %d r = %d q = %d\n", p, r, q);
        pthread_t lt;
        quick_sort(buffer, p, q-1);
        quick_sort(buffer, q+1, r);
    }
}

void printArray(int A[]) {
    for ( int i = 0 ; i < SIZE; i++) {
        cout << A[i] << ", ";
    }
    cout << endl;
}

int main() {
    cout << "Example of QuickSort, no need for the extra buffer[0] and sort same numbers" << endl;
    int array[SIZE];
    generateArray(array);
    printArray(array);
    quick_sort(array,0,9);
    printArray(array);

}