/**
 * @file readCSV.cpp
 * @brief Utility functions for reading postal code data from a CSV file.
 *
 * @course CSCI 331 - Software Systems — Fall 2025
 * @project Zip Code Group Project 1.0
 *
 * @details
 * This file defines functions that read U.S. postal code data stored in a CSV file
 * and populate a PostalList object. Each line of the CSV contains one postal record.
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
#include <fstream>

using namespace std;

/**
 * @brief Reads the CSV and adds each row to the list.
 *
 * The file has a header, then each line has 6 pieces:
 * ZIP, Place, State, County, Latitude, Longitude
 *
 * @param inputList Where we store all the items.
 * @param fileName  The CSV file we open.
 *
 * @pre
 *  - The CSV exists and we can open it.
 *  - Lines are simple comma-separated (no quotes/commas inside fields).
 * @post
 *  - Every good line becomes a PostalCodeItem in @p inputList.
 *  - The file is closed before we leave.
 *
 * @note We keep this simple on purpose. If the CSV has quotes or weird commas,
 *       this version won’t handle it.
 */

void inputCSVtoList(PostalList &inputList, string fileName)
{
    PostalCodeItem item;
    string line = "";
    int location = 0;

    ifstream myFile;
    myFile.open(fileName);

    // Skip the header: "zip,place,state,county,latitude,longitude"
    getline(myFile, line);

    while (getline(myFile, line))
    {
        // ZIP
        location = line.find(",");
        item.setZip(stoi(line.substr(0, location)));
        line = line.substr(location + 1, line.length());

        // Place
        location = line.find(",");
        item.setPlace(line.substr(0, location));
        line = line.substr(location + 1, line.length());

        // State
        location = line.find(",");
        item.setState(line.substr(0, location));
        line = line.substr(location + 1, line.length());

        // County
        location = line.find(",");
        item.setCounty(line.substr(0, location));
        line = line.substr(location + 1, line.length());

        // Latitude
        location = line.find(",");
        item.setLatitude(stod(line.substr(0, location)));
        line = line.substr(location + 1, line.length());

        // Longitude (last part of the line)
        item.setLongitude(stod(line));

        // Add it to our list
        inputList.addItem(item);
    }

    myFile.close();
}