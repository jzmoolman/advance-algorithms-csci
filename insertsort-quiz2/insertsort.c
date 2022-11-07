#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
    int count  = 50;

    srand(time(NULL));
    int ary[count];
    for (int i = 0; i < count; i++) {
      ary[i] = rand() %  10;
    }

    printf("Inserting sort\n");
    printf("Before sort [");
    for ( int i = 0; i < count; i++ ) {
      printf("%d,", ary[i]);
    }
    printf("]\n");


    for (int i = 1 ; i < count; i++ ) {
        for ( int j = i; j > 0; j-- ) {
          if (ary[j] < ary[j-1]) {
            int tmp = ary[j];
            ary[j] = ary[j-1];
            ary[j-1] = tmp;
          } else break;
        }
    }

    printf("After sort [");
    for ( int i = 0; i < count; i++ ) {
      printf("%d,", ary[i]);
    }
    printf("]\n");


}
