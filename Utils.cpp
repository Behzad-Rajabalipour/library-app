/***********************************************************************
// OOP244 Utils Module
// File	Utils.cpp
// Version
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
#include "Utils.h"
using namespace std;

namespace sdds {
	// Function to get an integer within a specified range
	int getInteger(int min, int max) {
		int number;
		for (int i = 0;; i++) {
			cin >> number;
			if (!cin || number < min || number > max) {				
				cout << "Invalid Selection, try again: ";
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else {
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
		}
		return number;
	}

}