/**
 * @file main2.cpp
 * @brief Our second main file for "Zip Code Group 4 Project 2.0" that output the postal sorted by state
 *
 * @course CSCI 331 - Software Systems — Fall 2025
 * @project Zip Code Group Project 1.0
 *
 * @details
 * We read a row randomized CSV (made from the XLSX), load each row into our list, and then print
 * the table the assignment asks for: one line per state (A–Z) showing, in this order,
 * the ZIPs that are farthest East (smallest longitude), West (biggest longitude),
 * North (biggest latitude), and South (smallest latitude). We also print a header first.
 *
 * @authors
 *  - Tran, Minh Quan
 *  - Asfaw, Abel
 *  - Kariniemi, Carson
 *  - Rogers, Mitchell
 *  - Farah, Mahad
 *
 *
 * @date Sep 23rd 2025
 * @version 1.0
 * @bug None that we know of right now.
 */

#include <string>
#include "PostalCodeItem.h"
#include "PostalList.h"
#include "readPostalCodeBuffer.cpp"

using namespace std;

/**
 * @brief Starts the program, loads the CSV, and prints the table.
 *
 * This main2.cpp will print the postal sorted by zip code.
 *
 * @return 0 if everything went fine.
 *
 * @pre The file @c us_postal_codes.csv is in the same folder and has the expected columns.
 * @post We write the header and then one row per state to standard output.
 */
int main()
{
     // Create a variable for csv file name
     string fileName = "us_postal_codes_ROWS_RANDOMIZED.csv";

     // Create an instance for PostalList
     PostalList myPostalList;

     // Input the data from the CSV file to the postal list
     inputCSVtoList(myPostalList, fileName);

     // Display the header with the appropriate table
     cout << "A table of all the postal sorted by zip from row randomized csv:" << endl
          << endl;
     cout << left << setw(10) << "Zip Code"
          << setw(20) << "Place Name"
          << setw(10) << "State"
          << setw(30) << "County"
          << setw(12) << "Latitude"
          << setw(12) << "Longitude"
          << endl;
     cout << "-----------------------------------------------------------------------------------------------" << endl;

     // Display the table sorted by zip
     myPostalList.printSortedByZip();

     return 0;
}