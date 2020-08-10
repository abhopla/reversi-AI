#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;


class Reversi{

    public:
    char board[8][9] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, 
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', 'W', 'B', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', 'B', 'W', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, };

    int num_of_valid_moves = 0;



    // print the current state of the game board
    void printBoard(){
        for (int i = 0; i < 72; i++){
            if(i%9!=8){
                cout<<" "<<board[i/9][i%9]; 
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


    // checks if input place has a piece already at position.
    // return 1 for position availible, 0 for position already taken 
    int check_position(int x, int y){

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
    int *legal_moves(char player){

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
                if (check_position(j, i) == 1){
                    // if player color is black
                    if (player == 'b'){
                        // position to the right is white
                        if ( board[i][j+1] == 'W'){
                            // check along the right of the position and confirm that there is a black piece after consecutive white pieces
                            int k = j+1;
                            while(k < 9){
                                if (board[i][k] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                            }
                        }
                        // position to the left is white
                        if (board[i][j-1] == 'W'){
                            // check along the left of the position and confirm that there is a black piece after consecutive white pieces
                            int k = j-1;
                            while(k >= 0){
                                if (board[i][k] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                            }
                        }
                        // position below is white
                        if (board[i+1][j] == 'W'){
                            // check along below the position and confirm that there is a black piece after consecutive white pieces
                            int k = i+1;
                            while(k < 8){
                                if (board[k][j] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                            }
                        }
                        // position above is white
                        if (board[i-1][j] == 'W'){
                            // check along above the position and confirm that there is a black piece after consecutive white pieces
                            int k = i-1;
                            while(k >= 0){
                                if (board[k][j] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                            }
                        }
                        // position to the bottom right is white
                        if (board[i+1][j+1] == 'W'){
                            // check along the diagonal (below right) position and confirm that there is a black piece after consecutive white pieces
                            int k = i+1;
                            int r = j+1;
                            while(k < 8 && r < 8 ){
                                if (board[k][r] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                                r++;
                            }
                        }
                        // position to the top right is white
                        if (board[i-1][j+1] == 'W'){
                            // check along the diagonal (above right) position and confirm that there is a black piece after consecutive white pieces
                            int k = i-1;
                            int r = j+1;
                            while(k >= 0 && r < 8){
                                if (board[k][r] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                                r++;
                            }
                        }
                        // position to the bottom left is white
                        if (board[i+1][j-1] == 'W'){
                            // check along the diagonal (above right) position and confirm that there is a black piece after consecutive white pieces
                            int k = i+1;
                            int r = j-1;
                            while(k < 8 && r >= 0){
                                if (board[k][r] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                                r--;
                            }
                        }
                        // position to the top left is white
                        if (board[i-1][j-1] == 'W'){
                            // check along the diagonal (below left) position and confirm that there is a black piece after consecutive white pieces
                            int k = i-1;
                            int r = j-1;
                            while(k >= 0 && r >= 0){
                                if (board[k][r] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
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
                                    goto afterLoop;
                                }
                                k++;
                            }
                        }
                        // position to the left is black
                        if (board[i][j-1] == 'B'){
                            // check along the left of the position and confirm that there is a white piece after consecutive white pieces
                            int k = j-1;
                            while(k >= 0){
                                if (board[i][k] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                            }
                        }
                        // position below is black
                        if (board[i+1][j] == 'B'){
                            // check along below the position and confirm that there is a white piece after consecutive white pieces
                            int k = i+1;
                            while(k < 8){
                                if (board[k][j] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                            }
                        }
                        // position above is black
                        if (board[i-1][j] == 'B'){
                            // check along above the position and confirm that there is a white piece after consecutive white pieces
                            int k = i-1;
                            while(k >= 0){
                                if (board[k][j] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                            }
                        }
                        // position to the bottom right is black
                        if (board[i+1][j+1] == 'B'){
                            // check along the diagonal (below right) position and confirm that there is a white piece after consecutive white pieces
                            int k = i+1;
                            int r = j+1;
                            while(k < 8 && r < 8 ){
                                if (board[k][r] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                                r++;
                            }
                        }
                        // position to the top right is black
                        if (board[i-1][j+1] == 'B'){
                            // check along the diagonal (above right) position and confirm that there is a white piece after consecutive white pieces
                            int k = i-1;
                            int r = j+1;
                            while(k >= 0 && r < 8){
                                if (board[k][r] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                                r++;
                            }
                        }
                        // position to the bottom left is black
                        if (board[i+1][j-1] == 'B'){
                            // check along the diagonal (above right) position and confirm that there is a white piece after consecutive white pieces
                            int k = i+1;
                            int r = j-1;
                            while(k < 8 && r >= 0){
                                if (board[k][r] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                                r--;
                            }
                        }
                        // position to the top left is black
                        if (board[i-1][j-1] == 'B'){
                            // check along the diagonal (below left) position and confirm that there is a white piece after consecutive white pieces
                            int k = i-1;
                            int r = j-1;
                            while(k >= 0 && r >= 0){
                                if (board[k][r] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                                r--;
                            }
                        }
                    }
                }
                // end of loop for each position
                afterLoop:;
                
            }
        }

        num_of_valid_moves = count;
        // cout << "this is the number of moves " << num_of_valid_moves << endl;
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
    int game_state(){

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



    // take user position input and place it on game board
    // make corresponding piece changes based on move
    void make_move(int position, int color){
        int * coordinates;

        coordinates = positionParse(position);

        int y = coordinates[0];
        int x = coordinates[1];

        //if player making move is player black
        if (color == 'b'){
            // check position above
            if (board[y-1][x] == 'W'){
                int k = y-1;
                while ( k >=0 ){
                    if (board[k][x] == 'B'){
                        while (k < y){
                            board[k+1][x] = 'B';
                            k++;
                        }
                        break;
                    }
                    k--;
                }
            }
            //check position top right diagonal
            if (board[y-1][x+1] == 'W'){
                int k = y-1;
                int r = x+1;
                while ( k >=0 && r < 8){
                    if (board[k][r] == 'B'){
                        while (k < y && r > x){
                            board[k+1][r-1] = 'B';
                            k++;
                            r--;
                        }
                        break;
                    }
                    k--;
                    r++;
                }
            }
            //check position right
            if (board[y][x+1] == 'W'){
                int k = x+1;
                while ( k < 8 ){
                    if (board[y][k] == 'B'){
                        while (k > x){
                            board[y][k-1] = 'B';
                            k--;
                        }
                        break;
                    }
                    k++;
                }
            }
            //check position bottom right diagonal
            if (board[y+1][x+1] == 'W'){
                int k = y+1;
                int r = x+1;
                while ( k < 8 && r < 8){
                    if (board[k][r] == 'B'){
                        while (k > y && r > x){
                            board[k-1][r-1] = 'B';
                            k--;
                            r--;
                        }
                        break;
                    }
                    k++;
                    r++;
                }
            }
            //check position below 
            if (board[y+1][x] == 'W'){
                int k = y+1;
                while ( k < 8 ){
                    if (board[k][x] == 'B'){
                        while (k > y){
                            board[k-1][x] = 'B';
                            k--;
                        }
                        break;
                    }
                    k++;
                }
            }
            //check position bottom left diagonal 
            if (board[y+1][x-1] == 'W'){
                int k = y+1;
                int r = x-1;
                while ( k < 8 && r >= 0){
                    if (board[k][r] == 'B'){
                        while (k > y && r < x){
                            board[k-1][r+1] = 'B';
                            k--;
                            r++;
                        }
                        break;
                    }
                    k++;
                    r--;
                }
            }
            //check position left  
            if (board[y][x-1] == 'W'){
                int k = x-1;
                while ( k >= 0 ){
                    if (board[y][k] == 'B'){
                        while (k < x){
                            board[y][k+1] = 'B';
                            k++;
                        }
                        break;
                    }
                    k--;
                }
            }
            //check position top left diagonal 
            if (board[y-1][x-1] == 'W'){
                int k = y-1;
                int r = x-1;
                while ( k >= 0 && r >= 0){
                    if (board[k][r] == 'B'){
                        while (k < y && r < x){
                            board[k+1][r+1] = 'B';
                            k++;
                            r++;
                        }
                        break;
                    }
                    k--;
                    r--;
                }
            }
        }
        //if player making move is player white
        else if(color == 'w'){
            // check position above
            if (board[y-1][x] == 'B'){
                int k = y-1;
                while ( k >=0 ){
                    if (board[k][x] == 'W'){
                        while (k < y){
                            board[k+1][x] = 'W';
                            k++;
                        }
                        break;
                    }
                    k--;
                }
            }
            //check position top right diagonal
            if (board[y-1][x+1] == 'B'){
                int k = y-1;
                int r = x+1;
                while ( k >=0 && r < 8){
                    if (board[k][r] == 'W'){
                        while (k < y && r > x){
                            board[k+1][r-1] = 'W';
                            k++;
                            r--;
                        }
                        break;
                    }
                    k--;
                    r++;
                }
            }
            //check position right
            if (board[y][x+1] == 'B'){
                int k = x+1;
                while ( k < 8 ){
                    if (board[y][k] == 'W'){
                        while (k > x){
                            board[y][k-1] = 'W';
                            k--;
                        }
                        break;
                    }
                    k++;
                }
            }
            //check position bottom right diagonal
            if (board[y+1][x+1] == 'B'){
                int k = y+1;
                int r = x+1;
                while ( k < 8 && r < 8){
                    if (board[k][r] == 'W'){
                        while (k > y && r > x){
                            board[k-1][r-1] = 'W';
                            k--;
                            r--;
                        }
                        break;
                    }
                    k++;
                    r++;
                }
            }
            //check position below 
            if (board[y+1][x] == 'B'){
                int k = y+1;
                while ( k < 8 ){
                    if (board[k][x] == 'W'){
                        while (k > y){
                            board[k-1][x] = 'W';
                            k--;
                        }
                        break;
                    }
                    k++;
                }
            }
            //check position bottom left diagonal 
            if (board[y+1][x-1] == 'B'){
                int k = y+1;
                int r = x-1;
                while ( k < 8 && r >= 0){
                    if (board[k][r] == 'W'){
                        while (k > y && r < x){
                            board[k-1][r+1] = 'W';
                            k--;
                            r++;
                        }
                        break;
                    }
                    k++;
                    r--;
                }
            }
            //check position left  
            if (board[y][x-1] == 'B'){
                int k = x-1;
                while ( k >= 0 ){
                    if (board[y][k] == 'W'){
                        while (k < x){
                            board[y][k+1] = 'W';
                            k++;
                        }
                        break;
                    }
                    k--;
                }
            }
            //check position top left diagonal 
            if (board[y-1][x-1] == 'B'){
                int k = y-1;
                int r = x-1;
                while ( k >= 0 && r >= 0){
                    if (board[k][r] == 'W'){
                        while (k < y && r < x){
                            board[k+1][r+1] = 'W';
                            k++;
                            r++;
                        }
                        break;
                    }
                    k--;
                    r--;
                }
            }
        }
    }

    // Checks whether the player wants to go first or second 
    // and validates the input 
    // sends back their answer 
    int validate_first_or_second(){
      int choice;
      cout << "Please choose whether you would like to 1st or 2nd! (1/2):  ";
      int check = 0;

      // This while loop is checking for invalid types 
      while(check == 0){
        while(!(cin >> choice)){
          cout << "Invalid type of argument! Please enter an integer to proceed: ";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if((choice == 1) || (choice == 2)){
          check = 1;
          break;
        }

        cout << "Invalid input please enter (1/2): ";


      }


      return choice;

    }


    // Purpose of this function is to validate 
    // player moves 
    // it needs the move and the color of their chips  
    int valid_player_choice(int color){
      int * legal_move_arr = legal_moves(color);
      int count = 0;
      int move = 0;
      int num_check = 0;
      int toggle = 0;


      cout << "These are the legal moves you are allowed to make: ";
      for(int i = 0; i < num_of_valid_moves; i++){
        cout<< legal_move_arr[i] << " ";
      }
      cout << "\n";
      cout << "Please select a move: ";

      while(num_check == 0){
        while(!(cin >> move)){
          cout << "Invalid type of argument! Please enter an integer to proceed: ";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        for(int j = 0; j < num_of_valid_moves; j++){
          if(legal_move_arr[j] != move){
              count ++;
              continue;
          } else{
              toggle = 1;
              num_check = 1;
              break;
          }

        }

        if(toggle == 0){
          cout << "Invalid input please try again: ";
        }

        


      } 

      


      return move;


    }



    // Function to determine how to play the game 
    //Gives the user the choice of going first 
    // or second 

    void play (){

        int choice = validate_first_or_second();
    
            if(choice == 1){
                cout << "You are going first! " << endl;
                int player_choice_1;
                int player_choice_2;
                int available_moves_1[64];
                int move_count = 0;
                int state_check = 0;

                while ((state_check == 0)){

                // First player goes 
                player_choice_1 = valid_player_choice('b');
                make_move(player_choice_1, 'b');

                cout << "This is the current board state: "<<endl;
                printBoard();

                //Second player goes
                player_choice_2 = valid_player_choice('w');
                make_move(player_choice_2, 'w');

                cout << "This is the current board state: "<<endl;
                printBoard();
                
                state_check = game_state();

                }

                
            }

            if(choice == 2){
            cout << "You are going second! " << endl;

            }

        }


};





