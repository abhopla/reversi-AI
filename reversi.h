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


// input current game state and player and return array of all legal moves
int legal_moves(char board[8][9], char player){

    int count = 0;
    
    //iterate through every position on board
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            // check for empty position
            if (check_position(board, j, i) == 1){
                // if player color is black
                if (player == 'b'){
                    // position to the right is white
                    if ( board[i][j+1] == 'W'){
                        // check along the right of the position and confirm that there is a black piece after consecutive white pieces
                        int k = j+1;
                        while(k < 9){
                            if (board[i][k] == 'B'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k++;
                        }
                    }
                    // position to the left is white
                    else if (board[i][j-1] == 'W'){
                        // check along the left of the position and confirm that there is a black piece after consecutive white pieces
                        int k = j-1;
                        while(k >= 0){
                            if (board[i][k] == 'B'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k--;
                        }
                    }
                    // position below is white
                    else if (board[i+1][j] == 'W'){
                        // check along below the position and confirm that there is a black piece after consecutive white pieces
                        int k = i+1;
                        while(k < 9){
                            if (board[k][j] == 'B'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k++;
                        }
                    }
                    // position above is white
                    else if (board[i-1][j] == 'W'){
                        // check along above the position and confirm that there is a black piece after consecutive white pieces
                        int k = i-1;
                        while(k >= 0){
                            if (board[k][j] == 'B'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k--;
                        }
                    }
                    // position to the bottom right is white
                    else if (board[i+1][j+1] == 'W'){
                        // check along the diagonal (below right) position and confirm that there is a black piece after consecutive white pieces
                        int k = i+1;
                        int r = j+1;
                        while(k < 9 && r < 9 ){
                            if (board[k][r] == 'B'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k++;
                            r++;
                        }
                    }
                    // position to the top right is white
                    else if (board[i-1][j+1] == 'W'){
                        // check along the diagonal (above right) position and confirm that there is a black piece after consecutive white pieces
                        int k = i-1;
                        int r = j+1;
                        while(k >= 0 && r < 9){
                            if (board[k][r] == 'B'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k--;
                            r++;
                        }
                    }
                    // position to the bottom left is white
                    else if (board[i+1][j-1] == 'W'){
                        // check along the diagonal (above right) position and confirm that there is a black piece after consecutive white pieces
                        int k = i+1;
                        int r = j-1;
                        while(k < 9 && r >= 0){
                            if (board[k][r] == 'B'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k++;
                            r--;
                        }
                    }
                    // position to the top left is white
                    else if (board[i-1][j-1] == 'W'){
                        // check along the diagonal (below left) position and confirm that there is a black piece after consecutive white pieces
                        int k = i-1;
                        int r = j-1;
                        while(k >= 0 && r >= 0){
                            if (board[k][r] == 'B'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k--;
                            r--;
                        }
                    }
                }
                // if player color is white
                else if (player == 'w'){
                    // position to the right is black
                    if ( board[i][j+1] == 'B'){
                        // check along the right of the position and confirm that there is a white piece after consecutive white pieces
                        int k = j+1;
                        while(k < 9){
                            if (board[i][k] == 'W'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k++;
                        }
                    }
                    // position to the left is black
                    else if (board[i][j-1] == 'B'){
                        // check along the left of the position and confirm that there is a white piece after consecutive white pieces
                        int k = j-1;
                        while(k >= 0){
                            if (board[i][k] == 'W'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k--;
                        }
                    }
                    // position below is black
                    else if (board[i+1][j] == 'B'){
                        // check along below the position and confirm that there is a white piece after consecutive white pieces
                        int k = i+1;
                        while(k < 9){
                            if (board[k][j] == 'W'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k++;
                        }
                    }
                    // position above is black
                    else if (board[i-1][j] == 'B'){
                        // check along above the position and confirm that there is a white piece after consecutive white pieces
                        int k = i-1;
                        while(k >= 0){
                            if (board[k][j] == 'W'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k--;
                        }
                    }
                    // position to the bottom right is black
                    else if (board[i+1][j+1] == 'B'){
                        // check along the diagonal (below right) position and confirm that there is a white piece after consecutive white pieces
                        int k = i+1;
                        int r = j+1;
                        while(k < 9 && r < 9 ){
                            if (board[k][r] == 'W'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k++;
                            r++;
                        }
                    }
                    // position to the top right is black
                    else if (board[i-1][j+1] == 'B'){
                        // check along the diagonal (above right) position and confirm that there is a white piece after consecutive white pieces
                        int k = i-1;
                        int r = j+1;
                        while(k >= 0 && r < 9){
                            if (board[k][r] == 'W'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k--;
                            r++;
                        }
                    }
                    // position to the bottom left is black
                    else if (board[i+1][j-1] == 'B'){
                        // check along the diagonal (above right) position and confirm that there is a white piece after consecutive white pieces
                        int k = i+1;
                        int r = j-1;
                        while(k < 9 && r >= 0){
                            if (board[k][r] == 'W'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k++;
                            r--;
                        }
                    }
                    // position to the top left is black
                    else if (board[i-1][j-1] == 'B'){
                        // check along the diagonal (below left) position and confirm that there is a white piece after consecutive white pieces
                        int k = i-1;
                        int r = j-1;
                        while(k >= 0 && r >= 0){
                            if (board[k][r] == 'W'){
                                cout << "i: " << i << " j: " << j << endl;
                                count++;
                            }
                            k--;
                            r--;
                        }
                    }
                }


            }

        }
    }

    return count;

}