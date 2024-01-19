// Header guard to prevent multiple inclusions of the same header file
#ifndef SDDS_DATE_H__
#define SDDS_DATE_H__

#include <iostream>

namespace sdds {
    // Global variables representing error codes and messages
    const int NO_ERROR = 0;
    const int CIN_FAILED = 1;
    const int YEAR_ERROR = 2;
    const int MON_ERROR = 3;
    const int  DAY_ERROR = 4;
    const char DATE_ERROR[5][16] = {
       "No Error",
       "cin Failed",
       "Bad Year Value",
       "Bad Month Value",
       "Bad Day Value"
    };

    // Constant representing the minimum valid year
    const int MIN_YEAR = 1500;

    // Date class declaration
    class Date {
    private:
        int m_year;        // Year component of the date
        int m_mon;         // Month component of the date
        int m_day;         // Day component of the date
        int m_ErrorCode;   // Error code for validation
        int m_CUR_YEAR;    // Current year used in the systemYear function

        // Private member functions
        int daysSince0001_1_1()const;  // Calculates the number of days since 0001-01-01
        bool validate();               // Validates the date
        void setToToday();             // Sets the date to the current system date
        void errCode(int);             // Sets the error code
        int systemYear()const;         // Retrieves the system year
        bool bad()const;               // Checks if there is an error
        int mdays()const;              // Calculates the number of days in the month

    public:
        // Constructors
        Date();                            // Default constructor
        Date(int year, int mon, int day);  // Parameterized constructor

        // Getter and setter functions
        std::istream& read(std::istream & = std::cin);   // Reads the date from input
        std::ostream& write(std::ostream & = std::cout)const;  // Writes the date to output
        int errCode()const;          // Retrieves the error code
        const char* dateStatus()const;  // Retrieves the date status message
        int currentYear()const;       // Retrieves the current year
        operator bool() const;        // Conversion operator to bool
        int daysSince0001_1_1_getter()const;  // Retrieves the days since 0001-01-01
        bool operator==(const Date& ob2)const;  // Equality comparison operator
        bool operator!=(const Date& ob2)const;  // Inequality comparison operator
    };

    // Global operators for input and output
    std::istream& operator>>(std::istream& istr, Date& RO);
    std::ostream& operator<<(std::ostream& ostr, const Date& RO);

    // Comparison operators
    bool operator>=(const Date& ob1, const Date& ob2);
    bool operator<=(const Date& ob1, const Date& ob2);
    bool operator<(const Date& ob1, const Date& ob2);
    bool operator>(const Date& ob1, const Date& ob2);
    int operator-(const Date& ob1, const Date& ob2);

    // Truly global variables
    extern bool sdds_test;  // External flag for testing
    extern int sdds_year;   // External variable for the year
    extern int sdds_mon;    // External variable for the month
    extern int sdds_day;    // External variable for the day
}

// End of header guard
#endif
