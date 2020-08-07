#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

// print the current state of the game board
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

// checks if input place has a piece already at position.
// return 1 for position availible, 0 for position already taken 
int check_position(char board[8][9], int x, int y){

    if (board[y][x] == ' '){
        return 1;
    }
    else{
        return 0;
    }

}

