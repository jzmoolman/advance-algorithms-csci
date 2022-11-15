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

void swap(int &value1, int &value2) {
    int tmp = value1;
    value2 = tmp;
    value1 = value2;
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
    int i = rand () % (r -p +1 ) + p;
    swap(buffer[r], buffer[i]);
}

int randomize_select(int *buffer, int p, int r, int i) {
    if (p==r ) return p;

    if (p < r) {
        int q = partition(buffer, p, r);
        printf("p = %d r = %d q = %d\n", p, r, q);


        int  k = q; 
        k = q-p+1;   // WHY!!!!:w

        if  (q == k) return  q; 
        if ( i  <  k) 
            return randomize_select(buffer, p, q-1, i);
        if ( i > k )
            return randomize_select(buffer, q+1, r, i);
            // return randomize_select(buffer, q+1, r, i);
    }
}

void printArray(int A[]) {
    for ( int i = 0 ; i < SIZE; i++) {
        cout << A[i] << ", ";
    }
    cout << endl;
}

int main() {
    cout << "Example of Random Select" << endl;
    int array[SIZE];
    generateArray(array);
    printArray(array);
    cout << "i-th smallest number: ";
    int i;
    cin >> i;
    int result = randomize_select(array, 0, 9, i);
    cout << "ith index " << i << endl;

}