#include <stdlib.h>
#include <iostream>
#include <string>
#include "reversi.h"

int main(){
    char board[8][9] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, 
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', 'W', 'B', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', 'B', 'W', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, };

    printBoard(board);

    int moves = legal_moves(board, 'G');
    cout <<"moves: " << moves << endl;
}