#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#include "reversi.h"

int main(){

    char test_board[8][9] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, 
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                    {' ', ' ', ' ', 'W', 'B', ' ', ' ', ' ', '\0'},
                    {' ', ' ', ' ', 'B', 'W', ' ', ' ', ' ', '\0'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}};


    Reversi game;

    // game.play();

    // game.playouts('b');

    int *moves = game.playouts_legal_moves('b', test_board);

    for (int i=0; i<4; i++){
        cout << moves[i] << endl;
    }

    game.playouts_make_move(19, 'b', test_board);

    for (int i = 0; i < 72; i++){
        if(i%9!=8){
            cout<<" "<<test_board[i/9][i%9]; 
            if(i%9<7)
                cout<<" |";
        }
        else{
            if(i/9<7)
                cout<<endl<< "---+---+---+---+---+---+---+---";
            cout<<endl; 
        }
    }
}