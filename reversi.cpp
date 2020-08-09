#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#include "reversi.h"

int main(){
    char board_2[8][9] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, 
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, };

    
    board_2[1][1] = 'G';

    int moves = game_state(board_2);
    cout <<"game: " << moves << endl;
    printBoard(board_2);

    // int moves = legal_moves(board_2, 'G');
    // cout <<"moves: " << moves << endl;

    play();
}