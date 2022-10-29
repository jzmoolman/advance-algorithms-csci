#include <iostream>
#include <list>

using namespace std;


int* board[9][9];

void initBoard() {
    for ( int i = 0; i < 9; i++) {
        for ( int j = 0; j < 9; j++) {
            board[i][j] = (int*)malloc(sizeof(int)*9);
            for ( int k = 0; k < 9; k++) {
                 *(board[i][j]+ k) = 1;
            }
        }
    }
}

void printBoard() {
     for (int i = 0; i < 1; i++) {
         for (int j = 0; j < 9; j++) {
            for ( int k = 0; k < 9; k++) {
               cout << *(board[i][j]+k) << ", ";
            }
        }
     }
}

int main() {

    cout << "Test 2: Suduku by JZ Moolman";
    initBoard();
    printBoard();


    return 0;
}