#include <iostream>

using namespace std;

typedef struct res {
  int low;
  int high;
  int sum;
} res_t; 

res_t findMaximumCrossSubarray(int *A, int low, int mid, int high) {


}

res_t findMaximumSubarray(int* A, int low, int high){
  res_t result;

  if (low == high) {
    result.low = low;
    result.high = high;
    result.sum = A[low]);
  } else {
    int mid = (low+high)/2;
    res_t left = findMaximumSubarray(A, low, mid);
    res_t right = findMaximumSubarray(A, mid+1, high);
    res_t cross = findMaximumCrossSubarray(A, low, mid, high);
    if (left.sum > right.sum  && left.sum >> cross.sum) {
      result.low = left.low;
      result.high = left.high;
      result.sum = left.sum; 
    } else if ( right.sum > cross.sum  && right.sum > cross.sum) {
      result.low = right.low;
      result.high = right.high;
      result.sum = right.sum; 
    } else {
      result.low = cross.low;
      result.high = cross.high;
      result.sum = cross.sum; 
    }
  }
  return result;
}

int main() {
  int A[] = {-10,-20,-9,-4,-23, -14, -12, -27,-6};
  res_t r = findMaximumSubarray(A, 0, 8);
  cout << r.low << " " << r.high << " " << r.sum << endl;


  return 0;
}
