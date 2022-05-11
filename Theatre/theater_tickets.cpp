/************************************
 *
 * Project 3: theater ticket and seating management
 *
 * File name: theater_tickets.cpp
 * Name: Collin Gabriel
 * Reviwer: Caleb Froelich
 *
 *
 *
 */

#include "theater_tickets_functions.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#define MAX_ROWS 25
#define MAX_COLS 50
using namespace std;

int getInt(string prompt) {
  int num;
  do {
    cout << prompt;
    if (!(cin >> num)) {
      cout << "Invalid entry. Please try again!" << endl;
      cin.clear();
      cin.ignore(100, '\n');
      continue;
    } else {
      return num;
    }
  } while (true);
}

void displaySeats(int numRows, int numCols,
                  const string arraySeats[][MAX_COLS]) {

  cout << setw(9 + static_cast<double>(numCols) / 2) << right << "Seats"
       << endl;
  for (int i = 0; i <= static_cast<double>(numCols) / 10; i++) {
    if (i == 0) {
      cout << setw(8) << right << i;
    } else if (i == 1) {
      cout << setw(9) << right << i;
    } else {
      cout << setw(10) << right << i;
    }
  }
  cout << endl;
  int j = 1;
  for (int i = 1; i <= numCols; i++) {
    if (j > 9) {
      j -= 10;
    }
    if (i == 1) {
      cout << setw(8) << right << j;
    } else {
      cout << j;
    }

    j++;
  }
  cout << endl;
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      if (j == 0) {
        cout << "Row " << i + 1;
        if (i < 9) {
          cout << setw(3) << right << arraySeats[i][j];
        } else if (i >= 9) {
          cout << setw(2) << right << arraySeats[i][j];
        }
      } else {
        cout << arraySeats[i][j];
      }
      if (j == numCols - 1) {
        cout << endl;
      }
    }
  }
  cout << endl;
}

void theaterSetup(const string EMPTY, int &numRows, int &numCols,
                  int &numSeatsSold, double &totalRevenue, int &rowSold,
                  int &colSold, string arraySeats[][MAX_COLS],
                  vector<double> &rowPrice) {
  numSeatsSold = 0;
  totalRevenue = 0;
  rowSold = 0;
  colSold = 0;
  bool validRowCol;
  do {
    validRowCol = true;
    numRows = getInt("Please enter the number of rows: [1-25] ");
    if (numRows > 25 || numRows < 0) {
      cout << "Please enter a value in the valid range. Rows [1-25]" << endl;
      validRowCol = false;
      continue;
    }
    numCols = getInt("Please enter the number of columns: [1-50] ");
    if (numCols > 50 || numCols < 0) {
      cout << "Please enter a value in the valid range. Columns [1-50]" << endl;
      validRowCol = false;
      continue;
    }
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {
        arraySeats[i][j] = EMPTY;
      }
    }
    cout << "Please enter the price of a seat in a given row." << endl;
    rowPrice.resize(numRows);
    for (int i = 0; i < numRows; i++) {
      cout << "Row " << i + 1 << ": $";
      cin >> rowPrice.at(i);
      if (rowPrice.at(i) < 0) {
          cout << "Please enter a valid price." << endl;
          i -= 1;
      }
    }
  } while (!validRowCol);
}

void sellingSeats(const string SOLD, int &rowSold, int &colSold, int numRows,
                  int numCols, string arraySeats[][MAX_COLS],
                  double &ticketPrice, double &totalRevenue,
                  vector<double> &rowPrice) {
  do {

    cout << "Enter a negative number to stop entering sold seats." << endl
         << endl;

    rowSold = getInt("Please enter the row of the sold seat: ");
    if (rowSold > numRows) {
      cout << "Error!  Please enter a value in the valid range of entered "
              "rows: [1-"
           << numRows << "] " << endl
           << endl;
      continue;
    } else if (rowSold < 0) {
      break;
    }
    colSold = getInt("Please enter the column of the sold seat: ");
    if (colSold > numCols) {
      cout << "Error!  Please enter a value in the valid range of entered "
              "columns: [1-"
           << numCols << "] " << endl
           << endl;
      continue;
    }
    cout << endl;
    if (colSold < 0) {
      break;
    }
    if (arraySeats[rowSold - 1][colSold - 1] == SOLD) {
      cout << "Error! This seat has already been sold." << endl;
      continue;
    } else {
      arraySeats[rowSold - 1][colSold - 1] = SOLD;
    }
    ticketPrice = rowPrice.at(rowSold - 1);
    totalRevenue += ticketPrice;
  } while (true);
}

void generalInformation(const string EMPTY, const string SOLD, int numRows,
                        int numCols, int numSeatsSold, int totalRevenue,
                        string arraySeats[][MAX_COLS],
                        vector<double> rowPrice) {

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      if (arraySeats[i][j] == SOLD) {
        numSeatsSold += 1;
      }
    }
  }
  cout << "Current number of tickets sold: " << numSeatsSold << endl;
  cout << "Current number of seats still available: "
       << (numRows * numCols) - numSeatsSold << endl;
  cout << "Current total revenue: $" << totalRevenue << endl;
  cout << "Rows with at least one seat available: " << endl;
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      if (arraySeats[i][j] == EMPTY) {
        cout << "Row " << i + 1 << ", $" << rowPrice.at(i) << " per ticket."
             << endl;
        break;
      }
    }
  }
  cout << endl;
}

int main() {
  string menuSelection;
  string arraySeats[MAX_ROWS][MAX_COLS];
  int numRows;
  int numCols;
  int i;
  int j;
  vector<double> rowPrice(1);
  double ticketPrice = 0;
  int rowSold;
  int colSold;
  double totalRevenue = 0;
  int numSeatsSold = 0;
  const string EMPTY = "_";
  const string SOLD = "$";

  theaterSetup(EMPTY, numRows, numCols, numSeatsSold, totalRevenue, rowSold,
               colSold, arraySeats, rowPrice);

  do {
    cout << endl << "Menu" << endl << endl;
    cout << "1)  Display seating chart" << endl;
    cout << "2)  Enter sold tickets" << endl;
    cout << "3)  Tickets sold, total seats available, "
            "current total revenue, and rows with at least one seat left"
         << endl;
    cout << "4)  Reset and enter new seating and pricing information" << endl;
    cout << "5)  Exit menu" << endl;
    cout << "Choose an option: ";
    cin >> menuSelection;
    cout << endl;
    // DISPLAY MENU
    if (menuSelection == "1") {
      displaySeats(numRows, numCols, arraySeats);

      // SEATING SALES & DISPLAYS MENU BEFORE AND
    } else if (menuSelection == "2") {
      displaySeats(numRows, numCols, arraySeats);
      sellingSeats(SOLD, rowSold, colSold, numRows, numCols, arraySeats,
                   ticketPrice, totalRevenue, rowPrice);
      displaySeats(numRows, numCols, arraySeats);

      // GENERAL INFORMATION
    } else if (menuSelection == "3") {
      generalInformation(EMPTY, SOLD, numRows, numCols, numSeatsSold,
                         totalRevenue, arraySeats, rowPrice);

      // RESET AND ENTER NEW VARIABLES
    } else if (menuSelection == "4") {
      theaterSetup(EMPTY, numRows, numCols, numSeatsSold, totalRevenue, rowSold,
                   colSold, arraySeats, rowPrice);

    } else if (menuSelection == "5") {
      cout << endl << "Thank you for using the theater seat tracker." << endl;
    } else {
      cout << "Please enter a valid menu option." << endl;
    }
    // EXIT MENU
  } while (menuSelection != "5");

  return 0;
}