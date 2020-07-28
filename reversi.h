#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

void printBoard(char board[3][4]){
    for (int i = 0; i < 12; i++)
    {
        if(i%4!=3)
        {
            cout<<" "<<board[i/4][i%4]; 
            if(i%4<2)
                cout<<" |";
        }
        else
        {
            if(i/4<2)
                cout<<endl<< "---+---+---";
            cout<<endl; 
        }
    }
}