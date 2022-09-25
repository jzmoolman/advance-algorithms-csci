#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 10

void merge(int* buffer, int p, int q, int r) {
    int n1 = q-p+1;
    int n2 = r-q;
    int L[n1+1];
    int R[n2+1];
    for ( int i = 0; i < n1; i++ ) {
      L[i] = *(buffer+(p+i));
    }

    for ( int i = 0; i < n2; i++ ) {
      R[i] = *(buffer+(q+i));
    }
    L[n1] = INT32_MAX;
    R[n2] = INT32_MAX;

    int i = 1;
    int j = 1;
    for (int k = p; k <= r;k++) {
      if (L[i] <= R[j] && L[i]) {
        *(buffer+k) = L[i];
        i++;
      } else {
        *buffer(+k) = R[j];
        j++;
      }
    }



}

void mergesort__(int* buffer, int p, int r) {

  if ( p < r ) {
      int q = (p + r)/2;
      mergesort__(buffer, p, q);
      mergesort__(buffer, p+1, r);
      merge(buffer,p,q,r);
  }
}

void generateBuffer(int* buffer, int size) {
  srand(time(NULL));
  for ( int i = 0; i < size; i++ ) {
    *(buffer+i) = rand() % 100 + 1;
  }
}

void printbuffer(int* buffer,int size) {
  printf("[");
  for ( int i = 0; i  < size; i ++ ) {
    printf("%d,",*(buffer+i));
  }
  printf("]\n");
}

int main(int argc, char** argv) {
  int array[BUFFER_SIZE] = {0};
  generateBuffer(array, BUFFER_SIZE);
  printbuffer(array, BUFFER_SIZE);



}
