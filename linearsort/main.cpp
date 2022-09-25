#include <iostream>
#include <time.h>

#define SIZE 10 

using namespace std;

void generateArray(int A[]) {
  srand(time(NULL));
  for ( int i = 0; i < SIZE; i++) {
    A[i] = rand() % 10 + 1;
  }
}

void printArray(int A[], int size) {
  cout << "[";
  for ( int i = 0; i < SIZE; i++) {
    cout << A[i] << ",";
  }
  cout << "]" << endl;
}

int search (int A[], int start, int end,  int key) {
    if ( A[start] == key  )
      return start;
    else {
      if ( start < end )
        return search(A, start+1,end, key );
      else return -1;
    }
}


int main() {
    int A[SIZE] = {0};
    generateArray(A);
    cout << "Initial Array: " << endl;
    printArray(A, SIZE);
    int key = 6;
    int result = search(A, 0, SIZE-1, key);
    
    cout << "Searching for " <<  key << endl;
    if (result < 0 ) { 
       cout << "Search failed " << endl;
    } else {
       cout << "fount at index " << result << endl;
    }

}     
