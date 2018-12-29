#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "Cell.h"



using std::string;
using std::cout;
using std::endl;
using std::cin;


void reset_board(Cell pointer[][Y_SIZE], string arg_string)
{
	for(int x=0; x<X_SIZE; x++)
	{
	  cout<<endl;
	  for(int y=0; y<Y_SIZE; y++)
	  {
		  pointer[x][y].current_state = arg_string;
		  pointer[x][y].next_state = arg_string;
	  }
	}
}

void print_board(Cell pointer[][Y_SIZE])
{	//Loops everywhere except the borders of the array
	for(int x=1; x<X_SIZE-1; x++)
	{	
	  cout<<'\n';
	  for(int y=1; y<Y_SIZE-1; y++)
	  {
		cout<<pointer[x][y].current_state;
	  }
	}
}

int prompt_seed()
{
	int seed = 0;
	cout<<"Enter a whole number that you want to seed the simulation with: ";
	cin>>seed;
	return seed;
}


void seed_populate_board(int seed, Cell pointer[][Y_SIZE])
{
	int x = 1;
	int y = 1;
	srand(seed);
	
	//Populate (roughly) one twentieth of the cells in the board. (I say roughly because the same X&Y could be generated more than once)
	for(int i=0; i<NUM_CELLS/ODDS_OF_STARTING; i++)
	{
		x = (1+rand() % (X_SIZE-1));
		y = (1+rand() % (Y_SIZE-1));
		//cout<<"X: "<<x<<" Y: "<<y<<endl;
		pointer[x][y].current_state = LIVE_CELL;
		pointer[x][y].next_state = LIVE_CELL;

	}
}

void check_neighbors(int x, int y, int &alive_neighbors, Cell pointer[][Y_SIZE])
{
	//Northwest neighbor
	if(pointer[x-1][y-1].current_state == LIVE_CELL)
		++alive_neighbors;
		
	//North neighbor
	if(pointer[x-1][y].current_state == LIVE_CELL)
		++alive_neighbors;
		
	//Northeast neighbor
	if(pointer[x-1][y+1].current_state == LIVE_CELL)
		++alive_neighbors;
		
	//East neighbor
	if(pointer[x][y+1].current_state == LIVE_CELL)
		++alive_neighbors;
		
	//Southeast neighbor
	if(pointer[x+1][y+1].current_state == LIVE_CELL)
		++alive_neighbors;
		
	//South neighbor
	if(pointer[x+1][y].current_state == LIVE_CELL)
		++alive_neighbors;
		
	//Southwest neighbor
	if(pointer[x+1][y-1].current_state == LIVE_CELL)
		++alive_neighbors;
		
	//West neighbor
	if(pointer[x][y-1].current_state == LIVE_CELL)
		++alive_neighbors;
	
	return;
}

void update_board(Cell pointer[][Y_SIZE])
{
	for(int x=1; x<X_SIZE-1; x++)
	{
		for(int y=1; y<Y_SIZE-1; y++)
		{
			pointer[x][y].current_state = pointer[x][y].next_state;
		}
	}
}

void run_life(Cell pointer[][Y_SIZE])
{	
	//These two variables will be shared by all cells on the board
	int num_alive_neighbors = 0;
	
	//Triple for loop. Iterators: i,x,y
	for(int i=0; i<NUM_CYCLES; i++)
	{	
		usleep(DELAY);
		print_board(pointer);

		for(int x=1; x<X_SIZE-1; x++)
		{	
			for(int y=1; y<Y_SIZE-1; y++)
			{	
				num_alive_neighbors = 0;
				
				check_neighbors(x, y, num_alive_neighbors, pointer);
				//cout<<"Num alive neighbors for cell "<<x<<","<<y<<": "<<num_alive_neighbors<<endl;
				
				//Change state of the cell 
				if(num_alive_neighbors < 2)
				{
					pointer[x][y].next_state = DEAD_CELL;
				}
				else
				{
					if(pointer[x][y].current_state == DEAD_CELL && num_alive_neighbors == 3)
					{
						pointer[x][y].next_state = LIVE_CELL;
					}
					else if(num_alive_neighbors > 3)
					{
						pointer[x][y].next_state = DEAD_CELL;
					}
				}
			}
		}
		
		update_board(pointer);
	}
}

void make_glider(Cell pointer[][Y_SIZE])
{
	pointer[1][2].next_state = LIVE_CELL;
	pointer[2][3].next_state = LIVE_CELL;
	pointer[3][1].next_state = LIVE_CELL;
	pointer[3][2].next_state = LIVE_CELL;
	pointer[3][3].next_state = LIVE_CELL;
	
	update_board(pointer);
	
	return;
}
#endif
