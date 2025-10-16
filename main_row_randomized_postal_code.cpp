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
     cout << "A table of all the postal sorted by zip:" << endl
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