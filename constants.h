using std::string;

const int X_SIZE = 60;
const int Y_SIZE = 226;
const int NUM_CELLS = X_SIZE * Y_SIZE;
const int ODDS_OF_STARTING = 5; //Approximately 1/10 cells will be populated for the first cycle.
const int NUM_CYCLES = 1000;
const int DELAY = 80000;
const string LIVE_CELL = "■";
const string DEAD_CELL = " ";
