#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

const int SIZE = 10;

void printArray(int A[], int size);

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

void swap(int &value1, int &value2) {
    int tmp = value2;
    value2 = value1;
    value1 = tmp;
}

int partition(int* buffer,int p, int r ) {
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

int random_partition(int buffer[], int p, int r)
{
    int i = rand () % (r - p + 1 ) + p;
                                                        // std::cout << "randin i " << i <<  std::endl;
    swap(buffer[r], buffer[i]);

    return partition(buffer, p, r);
}

int randomize_select(int *buffer, int p, int r, int i) {
    if (p==r ) return p;

    int q = random_partition(buffer, p, r);


    int k = q-p+1;   // WHY!!!!
    printf("p = %d r = %d q = %d k = %d\n", p, r, q, k);
    if  (i == k) return  q; 
    if ( i  <  k) 
        return randomize_select(buffer, p, q-1, i);
    if ( i > k )
        return randomize_select(buffer, q+1, r, i-k);
}

void printArray(int A[], int size) {
    for ( int i = 0 ; i < size; i++) {
        cout << A[i] << ", ";
    }
    cout << endl;
}

int main() {
    cout << "Example of Random Select" << endl;
    int array[SIZE];
    generateArray(array);
    printArray(array, SIZE);
    cout << "i-th smallest number: ";
    int i;
    cin >> i;
    int result = randomize_select(array, 0, SIZE-1, i);
    cout << "ith index " << result <<  " with value " << array[result] <<endl;

}