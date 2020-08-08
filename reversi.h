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


// input current game state and player and return array of all legal moves
int legal_moves(char board[8][9], char player){

    int count = 0;
    
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){

            if (check_position(board, j, i) == 1){
                // check if position has a piece next to it
                if(board[i][j+1] == 'B' || board[i][j-1] == 'B' || board[i+1][j] == 'B' || board[i-1][j] == 'B' || board[i][j+1] == 'W' || board[i][j-1] == 'W' || board[i+1][j] == 'W' || board[i-1][j] == 'W'){
                    cout << "i: " << i << " j: " << j << endl;
                    count++;
                }
            }

        }
    }

    return count;

}


int * positionParse (int pos){
  int coords[2];

  int y = floor((pos/8));
  int x  = (pos - (8 * y));

  coords[0] = y;
  coords[1] = x;

  return  coords;



}

// Parse the coordinates into a position 
int coordinates(int y, int x){
  int temp_y = y + 1;
  int pos = (temp_y*8) - (8 - x);


  return pos;


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
      cout << "invalid number please try again: ";
      cin >> choice;
      if((choice == 1) || (choice == 2)){
        check = 1;
      }

    }

        char board[8][9] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, 
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, };


    if(choice == 1){
      cout << "You are going first! ";
      int * coordinates;

      coordinates = positionParse(20);

      board[coordinates[0]][coordinates[1]] = 'A';

      printBoard(board);




    }

    if(choice == 2){
      cout << "You are going second! ";

    }

}