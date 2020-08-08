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

    int moves = game_state(board);
    cout <<"game: " << moves << endl;
}