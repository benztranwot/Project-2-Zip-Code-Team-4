#include <string>
#include "HeaderRecordPostalCodeItem.h"
#include "HeaderRecordPostalList.h"
#include <fstream>

using namespace std;

void inputCSVtoList(HeaderRecordPostalList &inputList, string fileName)
{
    HeaderRecordPostalCodeItem item;
    string line = "";
    int location = 0;

    ifstream myFile;
    myFile.open(fileName);

    // Skip the header: "zip,place,state,county,latitude,longitude"
    getline(myFile, line);

    while (getline(myFile, line))
    {
        // Record Length
        item.setRecordLength(stoi(line.substr(0, 2)));
        line = line.substr(3, line.length());
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