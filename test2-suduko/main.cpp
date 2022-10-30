#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define BRUTEFROCE_MAX  99


vector<int >* board[BRUTEFROCE_MAX][9][9];

int DEPTH = 0;

typedef struct {
    int row;
    int col;
    int value;
} BoardPos; 


stack<BoardPos> q;

void initBoard(int depth) {
    for ( int i = 0; i < 9; i++) {
        for ( int j = 0; j < 9; j++) {
            board[depth][i][j] = new vector<int>;
        }
    }
}

void resetBoard(int depth) {
    for ( int i = 0; i < 9; i++) {
        for ( int j = 0; j < 9; j++) {
         board[depth][i][j]->clear();
            for ( int k = 1; k < 10; k++) {
                board[depth][i][j]->push_back(k);
            }
        }
    }
}

void setPosition(int depth, int i, int j, int value) {
    board[depth][i][j]->clear();
    board[depth][i][j]->push_back(value);
}


void printPostion(int depth, int i, int j) {
    if ( board[depth][i][j]->size() > 1) {
        cout << "[" << i << "][" << j << "]";
        cout  << " = [";
        for ( vector<int>::iterator it = board[depth][i][j]->begin(); it != board[depth][i][j]->end(); it++) {
            cout << *it << ", ";
        }
        cout  << "]" << endl;
    } else if ( board[depth][i][j]->size() < 1) {
        cout << "[" << i << "][" << j << "]";
        cout << "Inconsistance state" << endl;

    }
}

void printPositions(int depth) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printPostion(depth,i,j);
        }
    }
}

int validSolution(int depth) {
    int result = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[depth][i][j]->size() != 1) {
                result = 0;
                break;
            }
        }
        if (result == 0) break;
    }
    return result;
}


void printBoard(int depth) {

     for (int i = 0; i < 9; i++) {
         if ( i> 0 && i % 3 == 0 ) {
            cout << "---------------" << endl;
         }
         for (int j = 0; j < 9; j++) {
            if ( j> 0 && j % 3 == 0 ) {
                cout << " | ";

            }
            if (board[depth][i][j]->size() == 1) {
                vector<int>::iterator it = board[depth][i][j]->begin();
                cout << *it;
            } else {
                cout <<  "*";
            }
        }
        cout << endl;
     }
}


void reducePosition(int depth, int i, int j) {
    if ( board[depth][i][j]->size() > 1) {
        /* reduce by row*/
        for(int col = 0; col < 9; col++) {
            if (col != j) {
                if ( board[depth][i][col]->size() == 1) {
                    int value = *(board[depth][i][col]->begin());
                    for( vector<int>::iterator it = board[depth][i][j]->begin(); it != board[depth][i][j]->end(); it++) {
                        if ( *it == value ) {
                            board[depth][i][j]->erase(it,it+1);
                            break;
                        }
                    }
                }
            }
        }
        // if (i == 4 && j == 1) printPostion(i,j);

        /* reduce by column*/
        for(int row = 0; row < 9; row++) {
            if (row != i) {
                if ( board[depth][row][j]->size() == 1) {
                    int value = *(board[depth][row][j]->begin());
                    for( vector<int>::iterator it = board[depth][i][j]->begin(); it != board[depth][i][j]->end(); it++) {
                        if ( *it == value ) {
                            board[depth][i][j]->erase(it,it+1);
                            break;
                        }
                    }
                }
            }
        }

        // if (i == 0 && j == 5) printPostion(i,j);
        /* reduce by box*/
        int box_row = (i) / 3;
        int box_col = (j) / 3;
        for(int row_offset = 0; row_offset < 3; row_offset++) {
            for(int col_offset = 0; col_offset < 3; col_offset++) {
                int row = box_row*3 + row_offset;
                int col = box_col*3 + col_offset;
                if (!(row == i && col == j)) {
                    if ( board[depth][row][col]->size() == 1) {
                        int value = *(board[depth][row][col]->begin());
                        for( vector<int>::iterator it = board[depth][i][j]->begin(); it != board[depth][i][j]->end(); it++) {
                            if ( *it == value ) {
                                board[depth][i][j]->erase(it,it+1);
                                break;
                            }
                        }
                    }
                }
            }
        }
        // if (i == 0 && j == 5) printPostion(i,j);
    }
}

// int reduceRowCount(int row) {
//     for ( int j = 0; j < 9; i++) {
//         vector<int> list;
//         if (board[depth][i][j]->size() > 1) {
//             for ( int k = 0; k < board[depth][row][j]->size(); k++ ) {
//                 list.push_back(board[depth][i][j].at(k));
//             }
//         }
//     }
// }

int getPositionSize(int depth, int i, int j) {
    return board[depth][i][j]->size();
}

void reduceBoard(int depth) {
    for( int i = 0; i < 9; i++) {
        for( int j = 0; j < 9; j++) {
            int pre = getPositionSize(depth, i,j);
            reducePosition(depth, i,j);
            if ( pre > 1 && getPositionSize(depth, i,j) == 1) { 
                reduceBoard(depth);
                break;
            }
        }
    }
}

void loadBoard1(int depth) {
    resetBoard(depth);
    setPosition(depth, 0,0,5);
    setPosition(depth, 0,1,3);
    setPosition(depth,0,4,7);
    setPosition(depth,1,0,6);
    setPosition(depth,1,3,1);
    setPosition(depth,1,4,9);
    setPosition(depth,1,5,5);
    setPosition(depth,2,1,9);
    setPosition(depth,2,2,8);
    setPosition(depth,2,7,6);
    setPosition(depth,3,0,8);
    setPosition(depth,3,4,6);
    setPosition(depth,3,8,3);
    setPosition(depth,4,0,4);
    setPosition(depth,4,3,8);
    setPosition(depth,4,5,3);
    setPosition(depth,4,8,1);
    setPosition(depth,5,0,7);
    setPosition(depth,5,4,2);
    setPosition(depth,5,8,6);
    setPosition(depth,6,1,6);
    setPosition(depth,6,6,2);
    setPosition(depth,6,7,8);
    setPosition(depth,7,3,4);
    setPosition(depth,7,4,1);
    setPosition(depth,7,5,9);
    setPosition(depth,7,8,5);
    setPosition(depth,8,4,8);
    setPosition(depth,8,7,7);
    setPosition(depth,8,8,9);
}

void loadBoard2(int depth) {
    resetBoard(depth);
    setPosition(depth,0,1,4);
    setPosition(depth,0,2,9);
    setPosition(depth,0,3,7);
    setPosition(depth,0,5,5);

    setPosition(depth,1,5,4);
    setPosition(depth,1,8,3);


    setPosition(depth,2,0,6);
    setPosition(depth,2,2,1);
    setPosition(depth,2,3,2);
    setPosition(depth,2,7,7);


    setPosition(depth,3,4,9);
    setPosition(depth,3,5,1);
    setPosition(depth,3,8,5);


    setPosition(depth,4,1,2);
    setPosition(depth,4,2,4);
    setPosition(depth,4,4,6);
    setPosition(depth,4,5,8);
    setPosition(depth,4,6,7);
    setPosition(depth,4,7,3);
    setPosition(depth,4,8,1);

    setPosition(depth,5,0,1);
    setPosition(depth,5,1,5);
    setPosition(depth,5,2,8);
    setPosition(depth,5,4,2);
    setPosition(depth,5,5,7);
    setPosition(depth,5,6,4);
    setPosition(depth,5,7,9);

    setPosition(depth,6,5,2);
    setPosition(depth,6,6,6);
    setPosition(depth,6,7,4);

    setPosition(depth,7,1,6);
    setPosition(depth,7,3,1);

    setPosition(depth,8,0,4);
    setPosition(depth,8,2,5);
    setPosition(depth,8,6,3);
    setPosition(depth,8,8,2);
}

void loadBoard3(int depth) {
    resetBoard(depth);
    setPosition(depth,0,2,1);
    setPosition(depth,0,5,7);
    setPosition(depth,0,7,8);
    setPosition(depth,0,8,4);

    setPosition(depth,1,2,9);
    setPosition(depth,1,4,1);
    setPosition(depth,1,6,2);
    
    setPosition(depth,2,2,7);
    setPosition(depth,2,3,5);
    setPosition(depth,2,5,4);


    setPosition(depth,3,0,1);
    setPosition(depth,3,2,8);
    setPosition(depth,3,3,3);
    setPosition(depth,3,5,9);
    setPosition(depth,3,8,5);
    
    setPosition(depth,4,1,4);
    setPosition(depth,4,3,1);
    setPosition(depth,4,4,7);
    setPosition(depth,4,7,3);
    
    setPosition(depth,5,7,9);

    setPosition(depth,6,7,7);

    setPosition(depth,7,0,8);
    setPosition(depth,7,4,3);

    setPosition(depth,8,0,7);
    setPosition(depth,8,4,8);
    setPosition(depth,8,5,2);
    setPosition(depth,8,6,5);
    setPosition(depth,8,8,1);
}

void copyBoard(int depth){
    for (int i= 0; i < 9; i++) {
        for (int j= 0; j < 9; j++) {
            board[depth][i][j]->clear();
            for ( vector<int>::iterator it = board[depth-1][i][j]->begin(); it != board[depth-1][i][j]->end(); it++) {
                board[depth][i][j]->push_back(*it);
            }
        }
    }
}

void findPositionMany(int depth, BoardPos* pos) {
    for (int i= 0; i < 9; i++) {
        for (int j= 0; j < 9; j++) {
            if (board[depth][i][j]->size() > 2 ) {
                pos->row = j;
                pos->col = i;
                pos->value = 0;
                return;
            }
        }
    }
    pos->row = -1;
    pos->col = -1;
    pos->value = -1;
    return ;
}

int main() {

    cout << "Test 2: Suduku by JZ Moolman" << endl;
    initBoard(DEPTH);
    loadBoard3(DEPTH);
    
    cout << "Initial board" << endl;
    printBoard(DEPTH);
    cout << endl;
    
    cout << "Reduced board" << endl;
    reduceBoard(DEPTH);
    printBoard(DEPTH);
    cout << endl;
   
    cout << "Position board" << endl;
    printPositions(DEPTH);

    if (validSolution(DEPTH)) {
        cout << "Solution found" << endl;
    } else {
        cout << "No solution found swithing to brute force mode" << endl;
        while (1) {
            DEPTH++;
            initBoard(DEPTH);
            copyBoard(DEPTH);
            BoardPos pos;
            findPositionMany(DEPTH,&pos);
            if (pos.row != -1) {
                int value = board[DEPTH][pos.row][pos.col]->at(0);
                board[DEPTH][pos.row][pos.col]->clear();
                board[DEPTH][pos.row][pos.col]->push_back(value);
                reduceBoard(DEPTH);
                printBoard(DEPTH);
                printPositions(DEPTH);
                if (validSolution(DEPTH)) { 
                    cout << "Solution found" << endl;
                    break;
                } else {
                    //DETROY BOARD
                    DEPTH--;
                    cout << "Purge invalid solution" << endl;
                    for( vector<int>::iterator it = board[DEPTH][pos.row][pos.col]->begin(); it != board[DEPTH][pos.row][pos.col]->end(); it++) {
                        if ( *it == value ) {
                            board[DEPTH][pos.row][pos.col]->erase(it,it+1);
                            break;
                        }
                    }
                }
            }
            cout << "Attempt XX" << endl;

        }
    }

    return 0;
}