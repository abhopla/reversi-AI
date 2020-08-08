#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>

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



int * positionParse (int pos){
  int coords[2];
  int *coordP = coords;

  int y = floor((pos/8));
  int x  = (pos - (8 * y));

  coords[0] = y;
  coords[1] = x;

  return  coordP;

}



// Parse the coordinates into a position 
int coordinates(int y, int x){
  int temp_y = y + 1;
  int pos = (temp_y*8) - (8 - x);

  return pos;

}



// input current game state and player and return array of all legal moves
int *legal_moves(char board[8][9], char player){

    int count = 0;
    static int moves_list[64];

    // set all array values to -1
    for (int i=0; i<64; i++){
        moves_list[i] = -1;
        // cout << moves_list[i] << " ";
    }
    
    // iterate through every position on board
    // i going down rows
    for (int i=0; i<8; i++){
        // j going left to right cols
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
                                moves_list[count] = coordinates(i, j);
                                // cout << moves_list[count] << endl;
                                // cout << count << endl;
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
                                moves_list[count] = coordinates(i, j);
                                count++;
                            }
                            k--;
                        }
                    }
                    // position below is white
                    else if (board[i+1][j] == 'W'){
                        // check along below the position and confirm that there is a black piece after consecutive white pieces
                        int k = i+1;
                        while(k < 8){
                            if (board[k][j] == 'B'){
                                moves_list[count] = coordinates(i, j);
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
                                moves_list[count] = coordinates(i, j);
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
                        while(k < 8 && r < 8 ){
                            if (board[k][r] == 'B'){
                                moves_list[count] = coordinates(i, j);
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
                        while(k >= 0 && r < 8){
                            if (board[k][r] == 'B'){
                                moves_list[count] = coordinates(i, j);
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
                        while(k < 8 && r >= 0){
                            if (board[k][r] == 'B'){
                                moves_list[count] = coordinates(i, j);
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
                                moves_list[count] = coordinates(i, j);
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
                        while(k < 8){
                            if (board[i][k] == 'W'){
                                moves_list[count] = coordinates(i, j);
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
                                moves_list[count] = coordinates(i, j);
                                count++;
                            }
                            k--;
                        }
                    }
                    // position below is black
                    else if (board[i+1][j] == 'B'){
                        // check along below the position and confirm that there is a white piece after consecutive white pieces
                        int k = i+1;
                        while(k < 8){
                            if (board[k][j] == 'W'){
                                moves_list[count] = coordinates(i, j);
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
                                moves_list[count] = coordinates(i, j);
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
                        while(k < 8 && r < 8 ){
                            if (board[k][r] == 'W'){
                                moves_list[count] = coordinates(i, j);
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
                        while(k >= 0 && r < 8){
                            if (board[k][r] == 'W'){
                                moves_list[count] = coordinates(i, j);
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
                        while(k < 8 && r >= 0){
                            if (board[k][r] == 'W'){
                                moves_list[count] = coordinates(i, j);
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
                                moves_list[count] = coordinates(i, j);
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

    static int *valid_moves = new int[count];

    for (int i=0; i<count; i++){
        valid_moves[i] = moves_list[i];
    }

    return valid_moves;
}



// check to see if game is complete
// if game incomplete return 0 
// if black win returns 1
// if white win returns 2
// if tie return 3
int game_state(char board[8][9]){

    int blk = 0;
    int whi = 0;

    // go through every position, if blank found return 0, otherwise count white and black tiles
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            
            if (board[i][j] == ' '){
                return 0;
            }
            else if (board[i][j] == 'B'){
                blk++;
            }
            else if (board[i][j] == 'W'){
                whi++;
            }
        }
    }

    if (blk > whi){
        return 1;
    }
    else if (blk < whi){
        return 2;
    }
    else if (blk == whi){
        return 3;
    }

    return 0;

}



// Function to determine how to play the game 
//Allows the player to choose the color of chip 
// they want 

void play (){
  int choice;
  cout << "Please choose whether you would like to 1st ot 2nd! (1/2):  ";
  int check = 0;

    // This while loop is checking for invalid types 
    while(!(cin >> choice)){
          cout << "Invalid type of argument! Please enter an integer to proceed: ";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if((choice == 1) || (choice == 2)){
      check = 1;
    }

    // This while loop checks for invalid numbers 
    while(check == 0){
      cout << "invalid number please try again: " << endl;
      cin >> choice;
      if((choice == 1) || (choice == 2)){
        check = 1;
      }

    }

    char board[8][9] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, 
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', 'W', 'B', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', 'B', 'W', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, };


    if(choice == 1){
      cout << "You are going first! " << endl;
      int * coordinates;

      coordinates = positionParse(20);

      board[coordinates[0]][coordinates[1]] = 'A';

      printBoard(board);

    }

    if(choice == 2){
      cout << "You are going second! " << endl;

    }

}