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
     cout << "A table of all the postal sorted by zip:" << endl
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