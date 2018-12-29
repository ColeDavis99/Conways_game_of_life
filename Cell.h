#include "constants.h"
using std::string;


struct Cell
{
	Cell() : current_state(DEAD_CELL), next_state(DEAD_CELL) {};
	
	string current_state;
	string next_state;
};
