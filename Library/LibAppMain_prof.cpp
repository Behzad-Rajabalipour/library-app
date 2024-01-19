/*
    Before Statring to test:
    1. Clear LibRecs.txt and LibRecsSmall.txt
    2. copy origLibRecs.txt into LibRecs.txt
    3. copy origLibRecsSmall.txt into LibRecsSmall.txt
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "LibApp.h"
#include "Date.h"
#include <cstring>
#include "iomanip"
#include "sstream"

// Function to center-align a string within a specified width
std::string centerAlign(const std::string& text, int width) {
    int padding = (width - text.length()) / 2;
    return std::string(padding, ' ') + text + std::string(padding, ' ');
}

void runLibApp(const char* filename) {
   char ch{};
   sdds::LibApp theApp(filename);
   theApp.run();
   std::ifstream file(filename);

   // Output header
   cout << centerAlign("Row", 6) << " | "
       << centerAlign("LocID", 5) << " | "
       << centerAlign("ShelfNo", 9) << "| "
       << centerAlign("Title", 41) << "| "
       << centerAlign("MemID", 6) << " | "
       << centerAlign("Date", 10) << " | "
       << centerAlign("Author", 24) << "| " << std::endl;

   // Output separator line
   std::cout << "------+-------+----------+------------------------------------------+-------+------------+-------------------------|" << std::endl;

   char line[500];
   // Read and print each line from the file
   while (file.getline(line, sizeof(line))) {
       char Row[5];
       char LocId[5];
       char ShelfNo[8]; // Adjusted for centered alignment
       char Title[50];
       char MemId[6];
       char Date[11];
       char Author[50];

       istringstream iss(line);
       
        iss.getline(Row, 50,'\t');
        iss.getline(LocId, 50, '\t');
        iss.getline(ShelfNo, 50, '\t');
        iss.getline(Title, 50, '\t');
        iss.getline(MemId, 50, '\t');
        iss.getline(Date, 50, '\t');
        iss.getline(Author, 50 ,'\n');

        // Truncate the displayed width of Title to 40 characters and add "..." if necessary
        string truncatedTitle = Title;
        if (truncatedTitle.length() > 37) {
            truncatedTitle = truncatedTitle.substr(0, 37) + "...";
        }


        string truncatedAuthor = Author;
        if (truncatedAuthor.length() > 20) {
            truncatedAuthor = truncatedAuthor.substr(0, 20) + "...";

        }

        // Print the values with centered alignment
        std::cout << centerAlign(Row, 5) << " | "
            << centerAlign(LocId, 5) << "  | " << centerAlign(ShelfNo, 8) << " | ";
        cout << setw(40) << left << truncatedTitle << " | " << centerAlign(MemId, 6) << " | " << centerAlign(Date, 11);
        cout << " | " << setw(23) << truncatedAuthor << " | " << std::endl; 
   }

   file.close();
}
int main() {
   sdds::sdds_day = 10;
   sdds::sdds_mon = 8;
   sdds::sdds_year = 2023;
   sdds::sdds_test = true;
   // runLibApp("LibRecsSmall.txt");      // Test for MS51, MS52, MS53, MS54
   runLibApp("LibRecs.txt");              // Test for MS55, MS56
   return 0;
}