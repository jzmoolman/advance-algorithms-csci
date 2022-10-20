#include <iostream>
#include <stdlib.h>
#include <time.h>

#define ArraySize 10

using namespace std;

void generateCandidate(int A[]){
  for (int i =0; i < ArraySize; i++) {
    A[i] = i;
  }
}


void printCandidate(int A[]) {

  for (int i =0; i < ArraySize; i++) {
    cout << A[i] << ", ";
  }
  cout  << endl;

}

void RandmizeInPlace(int A[]){
  int i, j, t;
  srand(time(NULL));
  for ( i =0; i <ArraySize; i++ ) {
    j = rand() % (10-i) + i;
    cout << "j " << j << endl;
     t = A[i];
    A[i] = A[j];
    A[j] = t;
  }
}

int main() {

  int candidate[ArraySize];
  generateCandidate(candidate);
  printCandidate(candidate);
  RandmizeInPlace(candidate);
  cout << "";
  printCandidate(candidate);
  exit(0);
}
