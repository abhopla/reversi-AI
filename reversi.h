#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#include <time.h>

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

    // Attribute made for the ai_vs_ai method 
    char start_board[8][9] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, 
                              {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                              {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                              {' ', ' ', ' ', 'W', 'B', ' ', ' ', ' ', '\0'},
                              {' ', ' ', ' ', 'B', 'W', ' ', ' ', ' ', '\0'},
                              {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                              {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                              {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, };

    char copy_board[8][9] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, 
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'}, };

    int num_of_valid_moves = 0;

    int playouts_valid_moves = 0;



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

    int count_black_tiles(){
      int black = 0;
        for (int i=0; i<8; i++){
          for (int j=0; j<9; j++){
            if(board[i][j] == 'B'){
              black ++;
            }    
        }
      }
      return black;
    }

    int count_white_tiles(){
      int white = 0;
        for (int i=0; i<8; i++){
          for (int j=0; j<9; j++){
            if(board[i][j] == 'W'){
              white ++;
            }    
        }
      }
      return white;
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
                                if (board[i][k] == ' '){
                                    break;
                                }
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
                                if (board[i][k] == ' '){
                                    break;
                                }
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
                                if (board[k][j] == ' '){
                                    break;
                                }
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
                                if (board[k][j] == ' '){
                                    break;
                                }
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
                                if (board[k][r] == ' '){
                                    break;
                                }
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
                                if (board[k][r] == ' '){
                                    break;
                                }
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
                                if (board[k][r] == ' '){
                                    break;
                                }
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
                                if (board[k][r] == ' '){
                                    break;
                                }
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
                                if (board[i][k] == ' '){
                                    break;
                                }
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
                                if (board[i][k] == ' '){
                                    break;
                                }
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
                                if (board[k][j] == ' '){
                                    break;
                                }
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
                                if (board[k][j] == ' '){
                                    break;
                                }
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
                                if (board[k][r] == ' '){
                                    break;
                                }
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
                                if (board[k][r] == ' '){
                                    break;
                                }
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
                                if (board[k][r] == ' '){
                                    break;
                                }
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
                                if (board[k][r] == ' '){
                                    break;
                                }
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
        // cout << "reg: this is the number of moves " << num_of_valid_moves << endl;
        static int *valid_moves = new int[count];

        for (int i=0; i<count; i++){
            valid_moves[i] = moves_list[i];
        }

        return valid_moves;
    }




    // legal_moves for the playouts copied board
    int *playouts_legal_moves(char player, char playout_board[8][9]){

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
                if (playout_board[i][j] == ' '){
                    // if player color is black
                    if (player == 'b'){
                        // position to the right is white
                        if ( playout_board[i][j+1] == 'W'){
                            // check along the right of the position and confirm that there is a black piece after consecutive white pieces
                            int k = j+1;
                            while(k < 9){
                                if (board[i][k] == ' '){
                                    break;
                                }
                                if (playout_board[i][k] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                            }
                        }
                        // position to the left is white
                        if (playout_board[i][j-1] == 'W'){
                            // check along the left of the position and confirm that there is a black piece after consecutive white pieces
                            int k = j-1;
                            while(k >= 0){
                                if (board[i][k] == ' '){
                                    break;
                                }
                                if (playout_board[i][k] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                            }
                        }
                        // position below is white
                        if (playout_board[i+1][j] == 'W'){
                            // check along below the position and confirm that there is a black piece after consecutive white pieces
                            int k = i+1;
                            while(k < 8){
                                if (board[k][j] == ' '){
                                    break;
                                }
                                if (playout_board[k][j] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                            }
                        }
                        // position above is white
                        if (playout_board[i-1][j] == 'W'){
                            // check along above the position and confirm that there is a black piece after consecutive white pieces
                            int k = i-1;
                            while(k >= 0){
                                if (board[k][j] == ' '){
                                    break;
                                }
                                if (playout_board[k][j] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                            }
                        }
                        // position to the bottom right is white
                        if (playout_board[i+1][j+1] == 'W'){
                            // check along the diagonal (below right) position and confirm that there is a black piece after consecutive white pieces
                            int k = i+1;
                            int r = j+1;
                            while(k < 8 && r < 8 ){
                                if (board[k][r] == ' '){
                                    break;
                                }
                                if (playout_board[k][r] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                                r++;
                            }
                        }
                        // position to the top right is white
                        if (playout_board[i-1][j+1] == 'W'){
                            // check along the diagonal (above right) position and confirm that there is a black piece after consecutive white pieces
                            int k = i-1;
                            int r = j+1;
                            while(k >= 0 && r < 8){
                                if (board[k][r] == ' '){
                                    break;
                                }
                                if (playout_board[k][r] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                                r++;
                            }
                        }
                        // position to the bottom left is white
                        if (playout_board[i+1][j-1] == 'W'){
                            // check along the diagonal (above right) position and confirm that there is a black piece after consecutive white pieces
                            int k = i+1;
                            int r = j-1;
                            while(k < 8 && r >= 0){
                                if (board[k][r] == ' '){
                                    break;
                                }
                                if (playout_board[k][r] == 'B'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                                r--;
                            }
                        }
                        // position to the top left is white
                        if (playout_board[i-1][j-1] == 'W'){
                            // check along the diagonal (below left) position and confirm that there is a black piece after consecutive white pieces
                            int k = i-1;
                            int r = j-1;
                            while(k >= 0 && r >= 0){
                                if (board[k][r] == ' '){
                                    break;
                                }
                                if (playout_board[k][r] == 'B'){
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
                        if ( playout_board[i][j+1] == 'B'){
                            // check along the right of the position and confirm that there is a white piece after consecutive white pieces
                            int k = j+1;
                            while(k < 8){
                                if (board[i][k] == ' '){
                                    break;
                                }
                                if (playout_board[i][k] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                            }
                        }
                        // position to the left is black
                        if (playout_board[i][j-1] == 'B'){
                            // check along the left of the position and confirm that there is a white piece after consecutive white pieces
                            int k = j-1;
                            while(k >= 0){
                                if (board[i][k] == ' '){
                                    break;
                                }
                                if (playout_board[i][k] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                            }
                        }
                        // position below is black
                        if (playout_board[i+1][j] == 'B'){
                            // check along below the position and confirm that there is a white piece after consecutive white pieces
                            int k = i+1;
                            while(k < 8){
                                if (board[k][j] == ' '){
                                    break;
                                }
                                if (playout_board[k][j] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                            }
                        }
                        // position above is black
                        if (playout_board[i-1][j] == 'B'){
                            // check along above the position and confirm that there is a white piece after consecutive white pieces
                            int k = i-1;
                            while(k >= 0){
                                if (board[k][j] == ' '){
                                    break;
                                }
                                if (playout_board[k][j] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                            }
                        }
                        // position to the bottom right is black
                        if (playout_board[i+1][j+1] == 'B'){
                            // check along the diagonal (below right) position and confirm that there is a white piece after consecutive white pieces
                            int k = i+1;
                            int r = j+1;
                            while(k < 8 && r < 8 ){
                                if (board[k][r] == ' '){
                                    break;
                                }
                                if (playout_board[k][r] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                                r++;
                            }
                        }
                        // position to the top right is black
                        if (playout_board[i-1][j+1] == 'B'){
                            // check along the diagonal (above right) position and confirm that there is a white piece after consecutive white pieces
                            int k = i-1;
                            int r = j+1;
                            while(k >= 0 && r < 8){
                                if (board[k][r] == ' '){
                                    break;
                                }
                                if (playout_board[k][r] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k--;
                                r++;
                            }
                        }
                        // position to the bottom left is black
                        if (playout_board[i+1][j-1] == 'B'){
                            // check along the diagonal (above right) position and confirm that there is a white piece after consecutive white pieces
                            int k = i+1;
                            int r = j-1;
                            while(k < 8 && r >= 0){
                                if (board[k][r] == ' '){
                                    break;
                                }
                                if (playout_board[k][r] == 'W'){
                                    moves_list[count] = coordinates(i, j);
                                    count++;
                                    goto afterLoop;
                                }
                                k++;
                                r--;
                            }
                        }
                        // position to the top left is black
                        if (playout_board[i-1][j-1] == 'B'){
                            // check along the diagonal (below left) position and confirm that there is a white piece after consecutive white pieces
                            int k = i-1;
                            int r = j-1;
                            while(k >= 0 && r >= 0){
                                if (board[k][r] == ' '){
                                    break;
                                }
                                if (playout_board[k][r] == 'W'){
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

        playouts_valid_moves = count;
        // cout << "playouts: this is the number of moves " << playouts_valid_moves << endl;
        static int *curr_moves = new int[count];

        for (int i=0; i<count; i++){
            curr_moves[i] = moves_list[i];
        }

        return curr_moves;
    }



   int num_of_tiles (){
     int blk = 0;
     int whi = 0;
        // go through every position, if blank found return 0, otherwise count white and black tiles
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                if (board[i][j] == 'B'){
                    blk++;
                }
                else if (board[i][j] == 'W'){
                    whi++;
                }
            }
        }

        if(blk > whi){
          return 1;
        } else if(whi > blk){
          return 2;
        } else if(blk == whi){
          return 3;
        }

        return 4;
   }


    // check to see if simulated game is complete
    // if game incomplete return 0 
    // if black win returns 1
    // if white win returns 2
    // if tie return 3
    int game_state(char color){

        int blk = 0;
        int whi = 0;

        legal_moves(color);


        // Check is the number of valid moves is 
        // 0 
        if(num_of_valid_moves == 0){
          return 0;
         
        }

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



    // checking game state for simulated playouts
    int playouts_game_state(char color, char playout_board[8][9]){

        int blk = 0;
        int whi = 0;

        playouts_legal_moves(color, playout_board);


        // Check is the number of valid moves is 
        // 0 
        if(playouts_valid_moves == 0){
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){

                    if (playout_board[i][j] == 'B'){
                        blk++;
                    }
                    else if (playout_board[i][j] == 'W'){
                        whi++;
                    }
                }
            }

            if(blk > whi){
              return 1;

            }
            else if(blk < whi){
              return 2;
            }
            else if(blk == whi){
              return 3;
            }

          
        }

        // go through every position, if blank found return 0, otherwise count white and black tiles
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                
                if (playout_board[i][j] == ' '){
                    return 0;
                }
                else if (playout_board[i][j] == 'B'){
                    blk++;
                }
                else if (playout_board[i][j] == 'W'){
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
    void make_move(int position, char color){
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
                    if (board[k][x] == ' '){
                        break;
                    }
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
                    if (board[k][r] == ' '){
                        break;
                    }
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
                    if (board[y][k] == ' '){
                        break;
                    }
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
                    if (board[k][r] == ' '){
                        break;
                    }
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
                    if (board[k][x] == ' '){
                        break;
                    }
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
                    if (board[k][r] == ' '){
                        break;
                    }
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
                    if (board[y][k] == ' '){
                        break;
                    }
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
                    if (board[k][r] == ' '){
                        break;
                    }
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
                    if (board[k][x] == ' '){
                        break;
                    }
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
                    if (board[k][r] == ' '){
                        break;
                    }
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
                    if (board[y][k] == ' '){
                        break;
                    }
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
                    if (board[k][r] == ' '){
                        break;
                    }
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
                    if (board[k][x] == ' '){
                        break;
                    }
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
                    if (board[k][r] == ' '){
                        break;
                    }
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
                    if (board[y][k] == ' '){
                        break;
                    }
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
                    if (board[k][r] == ' '){
                        break;
                    }
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



    // make_move but for random playouts on copy_board
    void playouts_make_move(int position, char color, char playout_board[8][9]){
        int * coordinates;

        coordinates = positionParse(position);

        int y = coordinates[0];
        int x = coordinates[1];

        //if player making move is player black
        if (color == 'b'){
            // check position above
            if (playout_board[y-1][x] == 'W'){
                int k = y-1;
                while ( k >=0 ){
                    if (board[k][x] == ' '){
                        break;
                    }
                    if (playout_board[k][x] == 'B'){
                        while (k < y){
                            playout_board[k+1][x] = 'B';
                            k++;
                        }
                        break;
                    }
                    k--;
                }
            }
            //check position top right diagonal
            if (playout_board[y-1][x+1] == 'W'){
                int k = y-1;
                int r = x+1;
                while ( k >=0 && r < 8){
                    if (board[k][r] == ' '){
                        break;
                    }
                    if (playout_board[k][r] == 'B'){
                        while (k < y && r > x){
                            playout_board[k+1][r-1] = 'B';
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
            if (playout_board[y][x+1] == 'W'){
                int k = x+1;
                while ( k < 8 ){
                    if (board[y][k] == ' '){
                        break;
                    }
                    if (playout_board[y][k] == 'B'){
                        while (k > x){
                            playout_board[y][k-1] = 'B';
                            k--;
                        }
                        break;
                    }
                    k++;
                }
            }
            //check position bottom right diagonal
            if (playout_board[y+1][x+1] == 'W'){
                int k = y+1;
                int r = x+1;
                while ( k < 8 && r < 8){
                    if (board[k][r] == ' '){
                        break;
                    }
                    if (playout_board[k][r] == 'B'){
                        while (k > y && r > x){
                            playout_board[k-1][r-1] = 'B';
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
            if (playout_board[y+1][x] == 'W'){
                int k = y+1;
                while ( k < 8 ){
                    if (board[k][x] == ' '){
                        break;
                    }
                    if (playout_board[k][x] == 'B'){
                        while (k > y){
                            playout_board[k-1][x] = 'B';
                            k--;
                        }
                        break;
                    }
                    k++;
                }
            }
            //check position bottom left diagonal 
            if (playout_board[y+1][x-1] == 'W'){
                int k = y+1;
                int r = x-1;
                while ( k < 8 && r >= 0){
                    if (board[k][r] == ' '){
                        break;
                    }
                    if (playout_board[k][r] == 'B'){
                        while (k > y && r < x){
                            playout_board[k-1][r+1] = 'B';
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
            if (playout_board[y][x-1] == 'W'){
                int k = x-1;
                while ( k >= 0 ){
                    if (board[y][k] == ' '){
                        break;
                    }
                    if (playout_board[y][k] == 'B'){
                        while (k < x){
                            playout_board[y][k+1] = 'B';
                            k++;
                        }
                        break;
                    }
                    k--;
                }
            }
            //check position top left diagonal 
            if (playout_board[y-1][x-1] == 'W'){
                int k = y-1;
                int r = x-1;
                while ( k >= 0 && r >= 0){
                    if (board[k][r] == ' '){
                        break;
                    }
                    if (playout_board[k][r] == 'B'){
                        while (k < y && r < x){
                            playout_board[k+1][r+1] = 'B';
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
            if (playout_board[y-1][x] == 'B'){
                int k = y-1;
                while ( k >=0 ){
                    if (board[k][x] == ' '){
                        break;
                    }
                    if (playout_board[k][x] == 'W'){
                        while (k < y){
                            playout_board[k+1][x] = 'W';
                            k++;
                        }
                        break;
                    }
                    k--;
                }
            }
            //check position top right diagonal
            if (playout_board[y-1][x+1] == 'B'){
                int k = y-1;
                int r = x+1;
                while ( k >=0 && r < 8){
                    if (board[k][r] == ' '){
                        break;
                    }
                    if (playout_board[k][r] == 'W'){
                        while (k < y && r > x){
                            playout_board[k+1][r-1] = 'W';
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
            if (playout_board[y][x+1] == 'B'){
                int k = x+1;
                while ( k < 8 ){
                    if (board[y][k] == ' '){
                        break;
                    }
                    if (playout_board[y][k] == 'W'){
                        while (k > x){
                            playout_board[y][k-1] = 'W';
                            k--;
                        }
                        break;
                    }
                    k++;
                }
            }
            //check position bottom right diagonal
            if (playout_board[y+1][x+1] == 'B'){
                int k = y+1;
                int r = x+1;
                while ( k < 8 && r < 8){
                    if (board[k][r] == ' '){
                        break;
                    }
                    if (playout_board[k][r] == 'W'){
                        while (k > y && r > x){
                            playout_board[k-1][r-1] = 'W';
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
            if (playout_board[y+1][x] == 'B'){
                int k = y+1;
                while ( k < 8 ){
                    if (board[k][x] == ' '){
                        break;
                    }
                    if (playout_board[k][x] == 'W'){
                        while (k > y){
                            playout_board[k-1][x] = 'W';
                            k--;
                        }
                        break;
                    }
                    k++;
                }
            }
            //check position bottom left diagonal 
            if (playout_board[y+1][x-1] == 'B'){
                int k = y+1;
                int r = x-1;
                while ( k < 8 && r >= 0){
                    if (board[k][r] == ' '){
                        break;
                    }
                    if (playout_board[k][r] == 'W'){
                        while (k > y && r < x){
                            playout_board[k-1][r+1] = 'W';
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
            if (playout_board[y][x-1] == 'B'){
                int k = x-1;
                while ( k >= 0 ){
                    if (board[y][k] == ' '){
                        break;
                    }
                    if (playout_board[y][k] == 'W'){
                        while (k < x){
                            playout_board[y][k+1] = 'W';
                            k++;
                        }
                        break;
                    }
                    k--;
                }
            }
            //check position top left diagonal 
            if (playout_board[y-1][x-1] == 'B'){
                int k = y-1;
                int r = x-1;
                while ( k >= 0 && r >= 0){
                    if (board[k][r] == ' '){
                        break;
                    }
                    if (playout_board[k][r] == 'W'){
                        while (k < y && r < x){
                            playout_board[k+1][r+1] = 'W';
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




    // Checks what type of AI the user wants to play against
    int ai_choice(){
      int choice;
      cout << "Please choose whether you would like to play against the Pure MCTS (1) or the heuritic based MCTS (2) (1/2):  ";
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



    // Checks which implementation should go first
    // in Ai vs Ai matches
    int ai_first_or_second(){
      int choice;
      cout << "Please choose which implementation should go first Pure MCTS(1) or the heuristic based MCTS(2) (1/2):  ";
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




    // Checks whether the player wants to go first or second 
    // and validates the input 
    // sends back their answer 
    int validate_first_or_second(){
      int choice;
      cout << "Please choose whether you would like to go 1st or 2nd or have the AI's play against each other(3)! (1/2/3):  ";
      int check = 0;

      // This while loop is checking for invalid types 
      while(check == 0){
        while(!(cin >> choice)){
          cout << "Invalid type of argument! Please enter an integer to proceed: ";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if((choice == 1) || (choice == 2) || (choice == 3)){
          check = 1;
          break;
        }

        cout << "Invalid input please enter (1/2/3): ";


      }


      return choice;

    }

    void show_poss_moves(char color){
      int * legal_move_arr = legal_moves(color);
      int move = 0;
      int y = 0;
      int x = 0;

      for(int i = 0; i < num_of_valid_moves; i++){
        int move = legal_move_arr[i];
          y = floor((move/8));
          x = (move - (8 * y));
          for (int i=0; i<8; i++){
            for (int j=0; j<9; j++){
                if((i == y) && (j == x)){
                  board[i][j] = 'O';
                }    
          }
        }
      }

    }

    void clear_board(){
      for(int i = 0; i < 8; i++){
        for(int j = 0; j<9; j++){
          if(board[i][j] == 'O'){
            board[i][j] = ' ';
          }
        }
      }
    }

    // Purpose of this function is to validate 
    // player moves 
    // it needs the color of their chips  
    int valid_player_choice(int color){
      int * legal_move_arr = legal_moves(color);
      int count = 0;
      int move = 0;
      int num_check = 0;
      int toggle = 0;

      // if(num_of_valid_moves == 0){
      //   return 0;
      // }


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




    // take board state and player color and return best move
    // Pure Monte-Carlo Tree Search Implementation
    int playouts_pure(char color){
        
        int *moves = legal_moves(color);
        int score = -999999;
        int choice = 0;

        if(num_of_valid_moves == 1){
          return moves[0];
        }

        // loop through each of the current valid moves
        for (int i=0; i<num_of_valid_moves; i++){

            int wins = 0;
            int ties = 0;
            int losses = 0;

            // Temporarily changing the random playouts
            // for testing 
            for (int k=0; k<5000; k++){

                // make copy_board reflect the curent state of the board
                for (int i=0; i<8; i++){
                    for (int j=0; j<9; j++){
                        copy_board[i][j] = board[i][j];
                    }
                }

                // make move of the current valid move
                playouts_make_move(moves[i], color, copy_board);

                // switch player color
                char curr_player_col = color;
                if (curr_player_col == 'b'){
                        curr_player_col = 'w';
                    }
                else if ( curr_player_col == 'w'){
                    curr_player_col = 'b';
                }


                // while game is not over
                while(playouts_game_state(curr_player_col, copy_board) == 0){

                    // get all legal moves 
                    int *move_options = playouts_legal_moves(curr_player_col, copy_board);

                    // play random position
                    int RandIndex = rand() % playouts_valid_moves;
                    playouts_make_move(move_options[RandIndex], curr_player_col, copy_board);

                    // switch colors for next move
                    if (curr_player_col == 'b'){
                        curr_player_col = 'w';
                    }
                    else if ( curr_player_col == 'w'){
                        curr_player_col = 'b';
                    }

                }

                if (playouts_game_state(curr_player_col, copy_board) == 1){
                    if (color == 'b'){
                        wins++;
                    }
                    else if (color == 'w'){
                        losses++;
                    }
                }
                else if (playouts_game_state(curr_player_col, copy_board) == 2){
                    if (color == 'w'){
                        wins++;
                    }
                    else if (color == 'b'){
                        losses++;
                    }
                }
                else if (playouts_game_state(curr_player_col, copy_board) == 3){
                    ties++;
                }

                

            }

            // cout << "Record for " << moves[i] << endl;
            // cout << "wins: " << wins << endl;
            // cout << "losses: " << losses << endl;
            // cout << "ties: " << ties << endl;
            // cout << endl;

            int combined_score = wins + ties - losses;

            if (combined_score > score){
                score = combined_score;
                choice = moves[i];
            }

        }

        // cout << "choice: " << choice << endl;
        cout << endl;

        return choice; 

    }



    // take board state and player color and return best move
    // Monte-Carlo Tree Search Heuristic Implementation
    int playouts_heur(char color){
        
        int *moves = legal_moves(color);
        int score = -99999999;
        int choice = 0;

        if(num_of_valid_moves == 1){
          return moves[0];
        }

        // loop through each of the current valid moves
        for (int i=0; i<num_of_valid_moves; i++){

            int wins = 0;
            int ties = 0;
            int losses = 0;

            // Temporarily changing the random playouts
            // for testing 
            for (int k=0; k<5000; k++){

                // make copy_board reflect the curent state of the board
                for (int i=0; i<8; i++){
                    for (int j=0; j<9; j++){
                        copy_board[i][j] = board[i][j];
                    }
                }

                // make move of the current valid move
                playouts_make_move(moves[i], color, copy_board);

                // switch player color
                char curr_player_col = color;
                if (curr_player_col == 'b'){
                        curr_player_col = 'w';
                    }
                else if ( curr_player_col == 'w'){
                    curr_player_col = 'b';
                }


                // while game is not over
                while(playouts_game_state(curr_player_col, copy_board) == 0){

                    // get all legal moves 
                    int *move_options = playouts_legal_moves(curr_player_col, copy_board);

                    // play random position
                    int RandIndex = rand() % playouts_valid_moves;
                    playouts_make_move(move_options[RandIndex], curr_player_col, copy_board);

                    // switch colors for next move
                    if (curr_player_col == 'b'){
                        curr_player_col = 'w';
                    }
                    else if ( curr_player_col == 'w'){
                        curr_player_col = 'b';
                    }

                }

                if (playouts_game_state(curr_player_col, copy_board) == 1){
                    if (color == 'b'){
                        wins++;
                    }
                    else if (color == 'w'){
                        losses++;
                    }
                }
                else if (playouts_game_state(curr_player_col, copy_board) == 2){
                    if (color == 'w'){
                        wins++;
                    }
                    else if (color == 'b'){
                        losses++;
                    }
                }
                else if (playouts_game_state(curr_player_col, copy_board) == 3){
                    ties++;
                }

                

            }

            // cout << "Record for " << moves[i] << endl;
            // cout << "wins: " << wins << endl;
            // cout << "losses: " << losses << endl;
            // cout << "ties: " << ties << endl;
            // cout << endl;

            int combined_score = wins + ties;

            // if any valid move is a corner piece, add 100k points essentially choosing that position
            if (moves[i] == 0 || moves[i] == 7 || moves[i] == 56 || moves[i] == 63){
                combined_score = combined_score + 100000;
            }

            // if a valid move is one space from corner spot, decrease points
            if (moves[i] == 1 || moves[i] == 8 || moves[i] == 9 || moves[i] == 6 || moves[i] == 14 || moves[i] == 15 || moves[i] == 48 || moves[i] == 49 || moves[i] == 57 || moves[i] == 54 || moves[i] == 55 || moves[i] == 62){
                combined_score = combined_score - 100000;
            }

            // if a valid move is two space off from the corner as an edge, increase points
            if (moves[i] == 2 || moves[i] == 5 || moves[i] == 16 || moves[i] == 23 || moves[i] == 40 || moves[i] == 47 || moves[i] == 58 || moves[i] == 611 ){
                combined_score = combined_score + 50000;
            }

            // // if a valid move is two space off from the corner in the middle, increase points
            // if (moves[i] == 18 || moves[i] == 21 || moves[i] == 42 || moves[i] == 45){
            //     combined_score = combined_score + 25000;
            // }
            

            // cout << "Score for " << moves[i] << ": " << combined_score << endl;

            if (combined_score > score){
                score = combined_score;
                choice = moves[i];
            }

        }

        return choice; 

    }



    // play the pure and heuristic versions against each other
    // will print results of matches
    // user decides number of matches
    void ai_vs_ai(int num_of_playouts){

        int chosen = ai_first_or_second();
        int turn = chosen;
        char pure_color;
        char heur_color;
        int heur_wins = 0;
        int pure_wins = 0;
        int ties = 0;

        // set colors based on which version was chose to go first
        if(turn == 1){
            pure_color = 'b';
            heur_color = 'w';
        }
        else if(turn == 2){
            pure_color = 'w';
            heur_color = 'b';
        }

        // loop through for each match
        for(int i=0; i<num_of_playouts; i++){

            for(int j=0; j<8; j++){
                for(int k=0; k<9; k++){
                    board[j][k] = start_board[j][k];
                }
            }

            int skip = 0;
            int compare;
            turn = chosen;

            // while game is not over
            while(game_state('b') == 0 && game_state('w') == 0){

                cout << "turn: " << turn << endl;

                if(skip > 1 && turn-compare == 1){
                    cout << "no more valid moves, game over" << endl;
                    break;
                }
 
                // if user chose pure to go first
                if(turn%2 == 1){
                    game_state(pure_color);
                    // cout << "valid moves: " << num_of_valid_moves << endl;
                    if (num_of_valid_moves == 0){
                        skip++;
                        compare = turn;
                        turn++;
                        // cout << "color:" << pure_color << "skip: " << skip << "compare: " << compare << "turn: " << turn << endl;
                        continue;
                    }
                    int pos = playouts_pure(pure_color);
                    // cout << "pos: " << pos << endl;
                    make_move(pos, pure_color);
                }
                // if user chose heuristic to go first
                else if(turn%2 == 0){
                    game_state(heur_color);
                    // cout << "valid moves: " << num_of_valid_moves << endl;
                    if (num_of_valid_moves == 0){
                        skip++;
                        compare = turn;
                        turn++;
                        // cout << "color:" << heur_color << "skip: " << skip << "compare: " << compare << "turn: " << turn << endl;
                        continue;
                    }
                    int pos = playouts_heur(heur_color);
                    // cout << "pos: " << pos << endl;
                    make_move(pos, heur_color);
                }
                skip = 0;
                printBoard();
                turn++;
            }
           
            // check result of completed game and record win, loss or tie     
            int result = num_of_tiles();

            if(chosen == 1){
                if(result == 1){
                    pure_wins ++;
                }else if(result == 2){
                    heur_wins ++;
                }else if(result == 3){
                    ties ++;
                }
            } else if(chosen == 2){
                if(result == 1){
                    heur_wins ++;
                }else if(result == 2){
                    pure_wins ++;
                }else if(result == 3){
                    ties ++;
                }
            }   

        }

        cout << "Pure wins: " << pure_wins << endl;
        cout << "Heur wins: " << heur_wins << endl;
        cout << "Ties: " << ties << endl;
    };


    int num_choice(){
      cout << "Please keep in mind that running a large number of playouts will result in slow execution! "<< endl;
      cout << endl;
      cout << "Please choose the number of playouts: ";
      int choice = 0;
        while(!(cin >> choice)){
          cout << "Invalid type of argument! Please enter an integer to proceed: ";
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return choice;
    }

    void welcome(){
      cout << "This is our implementation of reversi "<< endl;
      cout << "To play you must select the position you want on the board"<<endl;
      cout<<"the positions on the board go from 0 at the top left to 63 at the bottom right"<<endl;
      cout << "This is a representation of the positions on the board: "<<endl;
      for(int i =0; i<64; i++){
        cout << i << " ";
        if((i == 7) || (i == 15) || (i == 22) || (i == 29) || (i == 36) || (i == 43) || (i == 50) || (i == 57)){
          cout << endl;
        }
      }
      cout << endl;
      cout << "The 'O' character tells you which moves you are allowed to play on the board" <<endl;
      cout << endl;
    }
 
    // Function to determine how to play the game 
    // Gives the user the choice of going first 
    // or second 
    
    void play (){
        // welcome();

        int choice = validate_first_or_second();



            // If the player wants to go first 
            if(choice == 1){
                int ai_type = ai_choice();
                cout << "You are the black chip! " << endl;
                cout << endl;
                int player_choice_1;
                int player_choice_2;
                int state_check = 0;
                int black_tiles = 0;
                int white_tiles = 0;
                printBoard();

                //While the game is still going 
                while (state_check == 0){
                    int valid_checks = 0;

                    //Check the state of the game 
                    state_check = game_state('b');

                    // If valid moves are zero then skip to the next player 
                    if(num_of_valid_moves == 0){
                      cout << "There are no valid moves. Skipping turn!"<<endl;
                      valid_checks ++;
                        
                    }else{
                      // Player goes first
                      cout << "it's your turn!" << endl;
                      cout << endl;
                      player_choice_1 = valid_player_choice('b');
                      // show_poss_moves('b');
                      make_move(player_choice_1, 'b');
                      cout << "This is the current board state: "<<endl;
                      printBoard();
                      cout << endl;
                      clear_board ();
                    }

                    state_check = game_state('w');
                    if(num_of_valid_moves == 0){
                      cout << "There are no valid moves. Skipping turn!"<<endl;
                      if(valid_checks == 1){
                        break;
                      }

                    } else{
                         cout << "It's the AI's turn! "<<endl;
                         cout << endl;
                        //Second player goes
                        if(ai_type == 1){
                          player_choice_2 = playouts_pure('w');
                        } else if(ai_type == 2){
                          player_choice_2 = playouts_heur('w');
                        }
                        cout << "The AI picked: "<< player_choice_2 << endl;
                        cout << endl;
                        make_move(player_choice_2, 'w');

                        show_poss_moves('b');
                        cout << "This is the current board state: "<<endl;
                        printBoard();
                        cout << endl;
                        cout << "The 'O' character tells you which moves you are allowed to play on the board" <<endl;
                        black_tiles = count_black_tiles();                      
                        white_tiles = count_white_tiles();
                        cout << endl;
                        cout << "The current board state is: " << black_tiles << " black tiles and " << white_tiles<<" white tiles" << endl;
                        cout << endl;
                        clear_board ();
                    }

                

                }
                state_check = num_of_tiles();

                if(state_check == 1){
                  cout << "You Win! " <<endl;
                } 
                else if(state_check == 2){
                  cout << "You Lose! " <<endl;
                }
                else if(state_check == 3){
                  cout << "The game is a tie!"<<endl;
                }

                
            }

            // If the player wants to go second 
            if(choice == 2){
                int ai_type = ai_choice();
                cout << "You are the white chip! " << endl;
                cout << endl;
                int player_choice_1;
                int player_choice_2;
                int state_check = 0;
                int black_tiles = 0;
                int white_tiles = 0;

                while (state_check == 0){
                    int valid_checks = 0;
                    state_check = game_state('b');
                    if(num_of_valid_moves == 0){
                      cout << "There are no valid moves. Skipping turn!"<<endl;
                      valid_checks ++;
                    } else{
                      cout << endl;
                      //AI goes first 
                      if(ai_type == 1){
                        player_choice_1 = playouts_pure('b');
                      } else if(ai_type == 2){
                        player_choice_1 = playouts_heur('b');
                      }
                      cout << "The AI picked: "<< player_choice_1 << endl;
                      cout << endl;
                      make_move(player_choice_1, 'b');
                      show_poss_moves('w');
                      cout << "This is the current board state: "<<endl;
                      printBoard();
                      cout << endl;
                      cout << "The 'O' character tells you which moves you are allowed to play on the board" <<endl;
                      black_tiles = count_black_tiles();                      
                      white_tiles = count_white_tiles();
                      cout << endl;
                      cout << "The current board state is: " << black_tiles << " black tiles and " << white_tiles<<" white tiles" << endl;
                      cout << endl;
                      clear_board ();

                    }

                    state_check = game_state('w');
                    if(num_of_valid_moves == 0){
                      cout << "There are no valid moves. Skipping turn!"<<endl;
                      if(valid_checks == 1){
                        break;
                      }
                    } else{
                      // Player goes second
                      cout << "it's your turn!" << endl;
                      cout << endl; 
                      player_choice_2 = valid_player_choice('w');
                      make_move(player_choice_2, 'w');
                      cout << endl;
                      cout << "This is the current board state: "<<endl;
                      printBoard();
                      cout << endl;
                    }

                }
                state_check = num_of_tiles();

                if(state_check == 1){
                  cout << "You Win! " <<endl;
                } 
                else if(state_check == 2){
                  cout << "You Win! " <<endl;
                }
                else if(state_check == 3){
                  cout << "The game is a tie!"<<endl;
                }


            }

            if(choice == 3){
                // cout << "The different implementations of AI will play against each other!" << endl;
                int choice = num_choice();
                ai_vs_ai(choice);



            }

        }


};




