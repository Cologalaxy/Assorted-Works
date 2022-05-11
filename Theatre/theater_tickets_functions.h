#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#define MAX_ROWS 25
#define MAX_COLS 50
using namespace std;

// checks to see if the inputed value is an integer. 
// If it is, it returns that integer to the appropriate variable, 
// but if not, it will loop and clear the input until the user gives a valid integer input.
int getInt(string prompt);

// Displays the seats. More specifically, shows which seats are available (denoted by a "_") and
// which are not (denoted by a "$").
void displaySeats(int numRows, int numCols, const string arraySeats[][MAX_COLS]); 
                  
// Resets all the incremental variables, and gets the user to input data for the
// rows, columns, and pricing
void theaterSetup(int &numRows, int &numCols, int &numSeatsSold, double &totalRevenue, int &rowSold, int &colSold, string arraySeats[][MAX_COLS], vector<double> &rowPrice);

// A do while loop allowing the user to enter seats that are sold based on the
// row and column. It also keeps track of how much each seat costs and how much
// total revenue has been acrued from ticket sales
void sellingSeats(int &rowSold, int &colSold, string arraySeats[][MAX_COLS], double &ticketPrice, double &totalRevenue, vector<double> &rowPrice);

// Displays the number of tickets sold, how many seats are still available, how
// much total revenue has been accrued, and which rows still have at least one
// seat available and how much a seat in that row costs.
void generalInformation(int numRows, int numCols, int numSeatsSold,
                        int totalRevenue, const string arraySeats[][MAX_COLS],
                        vector<double> rowPrice);
