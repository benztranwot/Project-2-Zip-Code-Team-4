/**
 * @file main3.cpp
 * @brief Our third main file for "Zip Code Group 4 Project 2.0" that output the postal sorted by zip code
 *
 * @course CSCI 331 - Software Systems — Fall 2025
 * @project Zip Code Group Project 1.0
 *
 * @details
 * We read data from a file structure format with length indicated header record,
 * load each row into our list, and then print the table the assignment asks for:
 * one line per state (A–Z) showing, in this order, the header record with length indicated,
 * the ZIPs that are farthest East (smallest longitude), West (biggest longitude),
 * North (biggest latitude), and South (smallest latitude).
 *
 * @authors
 *  - Tran, Minh Quan
 *  - Asfaw, Abel
 *  - Kariniemi, Carson
 *  - Rogers, Mitchell
 *  - Farah, Mahad
 *
 *
 * @date Oct 16th 2025
 * @version 1.0
 * @bug None that we know of right now.
 */

#include <string>
#include "HeaderRecordPostalCodeItem.h"
#include "HeaderRecordPostalList.h"
#include "readHeaderRecordPostalCodeBuffer.cpp"

using namespace std;

int main()
{
     // Create a variable for csv file name
     string fileName = "us_postal_codes_length_indicated_header_record.txt";

     // Create an instance for HeaderRecordPostalList
     HeaderRecordPostalList myHeaderRecordPostalList;

     // Input the data from the CSV file to the postal list
     inputCSVtoList(myHeaderRecordPostalList, fileName);

     // Display the header with the appropriate table
     cout << "A table of all the postal sorted by zip from length indicated records:" << endl
          << endl;
     cout << left << setw(5) << "HR"
          << setw(10) << "Zip Code"
          << setw(20) << "Place Name"
          << setw(10) << "State"
          << setw(30) << "County"
          << setw(12) << "Latitude"
          << setw(12) << "Longitude"
          << endl;
     cout << "-----------------------------------------------------------------------------------------------" << endl;

     // Display the table sorted by zip
     myHeaderRecordPostalList.printSortedByZip();

     return 0;
}