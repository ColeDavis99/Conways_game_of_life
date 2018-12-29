#include "functions.h"

int main()
{  
  int seed = 0;
  
  
  //Declare the board
  Cell board[X_SIZE][Y_SIZE];
  
  //Make the board blank, and the next state blank 
  reset_board(board, DEAD_CELL);
  
  //Ask the user for a seed 
  seed = prompt_seed();
  
  //Populate the board with the specified seed.
  seed_populate_board(seed, board);
  
  //make_glider(board);
  
  //Run the simulation for NUM_CYCLES times.
  run_life(board);
  return 0;
}

