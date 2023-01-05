#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>


using namespace std;

void print_tableu(vector<vector<int> > &t){
    for ( int i = 0; i < t.size(); i++) {
        for ( int j= 0; j < t.at(i).size(); j++) {
            cout << t.at(i).at(j) << " | ";
        }
        cout << endl;
    }
}

void init_tableau(vector<vector<int> > &t, int size) {
    int m = size;
    for ( int i = 0; i < m; i++) {
        vector<int> row;
        for ( int j= 0; j < m; j++) {
            row.push_back(-1);
        }
        t.push_back(row);
    }
    
}

void insert_key(vector<vector<int> > &t, int key){
    /* using the bump algorithm */
    for ( int i = 0; i < t.size(); i++){
        for ( int j= 0; j < t.size(); j++){
            if (t.at(i).at(j) == -1) {
                t.at(i).at(j) = key;
                return;
            } else if (key <  t.at(i).at(j)) {
                swap(key, t.at(i).at(j));
                break;
            }
         }
    }
}


void fix_tableau(vector<vector<int> > &t, int i, int j) {
    int m = t.size();
    int n = t.at(0).size();
    int b; // bottum of current
    int r; // right of current
    if ( i + 1 < m ) 
        b = t.at(i+1).at(j);
    else 
        b = -1;
        
    
    if ( j + 1 < n ) 
        r = t.at(i).at(j+1);
    else 
        r = -1;
    
                                                          
                                                        // cout << "fix_tableau: i, j " << i << " "<<  j << endl;
                                                        // cout << "fix_tableau: b, r " << b << " "<<  r << endl;
    
    /* base cse */
    if ( b == -1 && r == -1)
        return;
    
    if (b == -1)  {
        swap(t.at(i).at(j), t.at(i).at(j+1));
        fix_tableau(t, i, j+1);
    } else if ( r == -1) {
        swap(t.at(i).at(j), t.at(i+1).at(j));
        fix_tableau(t, i+1, j);
    } else  if (b < r ) {
        swap(t.at(i).at(j), t.at(i+1).at(j));
        fix_tableau(t, i+1, j);
    } else {
        // cout << "----> "<< j <<  t.at(i).at(j+1);
        swap(t.at(i).at(j), t.at(i).at(j+1));
        fix_tableau(t, i, j+1);
    }
}

void delete_key(vector<vector<int> > &t, int i, int j) {
    t.at(i).at(j) = -1;
    fix_tableau(t, i, j);
}

int is_empty1(vector<vector<int> > &t) {

    if ( t.at(0).at(0)  == -1 )
        return 1;
    else 
        return 0;
    
}

int extract_min(vector<vector<int> > &t) {
    if ( is_empty1(t) == 1 )  {
       perror("vector is empty");
       exit(1);
    }
    int result = t.at(0).at(0);
    delete_key(t, 0,0);
    return result;

}

int main() {
    
    cout << "Project II, JZ Moolman" << endl;

    vector<int> v;
    v.push_back(9);
    v.push_back(16);
    v.push_back(3);
    v.push_back(2);
    v.push_back(4);
    v.push_back(8);
    v.push_back(5);
    v.push_back(14);
    v.push_back(12);
    
    vector< vector<int> > tableau;

    init_tableau(tableau, 4);
    for (int i = 0; i < v.size();i++)
       insert_key(tableau, v.at(i));
    cout << "Task I" << endl;
    print_tableu(tableau);
    cout << endl;

    cout << "Task II" << endl;
    print_tableu(tableau);
    cout << endl;
    
    while (is_empty1(tableau) == 0) {
        int min = extract_min(tableau);
        // print_tableu(tableau);
        cout << endl;
        cout << min << ", ";
    }
    
        cout << endl;

    

}