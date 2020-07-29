#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

void printBoard(char board[8][9]){
    for (int i = 0; i < 72; i++)
    {
        if(i%9!=8)
        {
            cout<<" "<<board[i/9][i%9]; 
            if(i%9<7)
                cout<<" |";
        }
        else
        {
            if(i/9<7)
                cout<<endl<< "---+---+---+---+---+---+---+---";
            cout<<endl; 
        }
    }
}