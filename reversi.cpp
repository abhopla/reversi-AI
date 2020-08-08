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

    printBoard(board_2);

    int moves = legal_moves(board_2, 'G');
    cout <<"moves: " << moves << endl;

    play();
}