#include <iostream>
#include <stdlib.h>
#include <time.h>

#define SIZE 10 

using namespace std;

void generateArray(int A[]) {
  srand(time(NULL));
  for ( int i = 0; i < SIZE; i++) {
    A[i] = rand() % 100 + 1;
  }
}

void printArray(int A[], int size) {
  
  for ( int i = 0; i < SIZE; i++) {
    cout << A[i];
  }
}


void Merge (int A[], int p, int q, int r) {
    int n1, n2, *L, *R ,i, j;
    n1 = q - p + 1;
    n2 = r - q;
    R = new int[n1 + 1];
    L = new int[n2 + 1];

    for (i = 0; i < n1; i++) 
      L[i] = A[p+i];
    
    for (i = 0; i < n2; i++) 
      R[i] = A[q+1+i];
    
    L[n1] = INT32_MAX;
    R[n2] = INT32_MAX;
    i = 0;
    j = 0;
    for (int k = p; k <=r; k++) {
        if (( L[i] != INT32_MAX) && (L[i] <= R[j])) {
            if (L[i] <= R[i]) {
              A[k] = L[i];
              i++;
          } else {
              A[k] = R[j];
              j++;
          }
        }
    }
}


void MergeSort(int All. int p, int r) {
  int q;
  if (p < r) {
    q = (p +r) /2;
    MergeSort(A, p, q):
    MergeSort(A, q + 1, r);
    Merge(A, p. q, r);
  }
}

int main() {
    int A[SIZE] = {0};
    generateArray(A);
    cout << "Initial Array: ";
    printArray(A, SIZE);
    MergeSort(A,0,SIZE-1);
    printArray(A, SIZE);
}    
