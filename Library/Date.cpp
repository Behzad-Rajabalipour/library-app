// Include necessary headers
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "iomanip"
#include "Date.h"

using namespace std;
namespace sdds {
    // Global variables
    bool sdds_test = false;          // Boolean flag for testing purposes, set to true in testing scenarios
    int sdds_year = 2023;            // Default year for non-test scenarios
    int sdds_mon = 12;                // Default month for non-test scenarios
    int sdds_day = 25;                // Default day for non-test scenarios

    // Function to validate the date
    bool Date::validate() {
        errCode(NO_ERROR);

        if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1) {
            errCode(YEAR_ERROR);
            cerr << "Year must be between 1500 and current year\n";
        }
        else if (m_mon < 1 || m_mon > 12) {
            errCode(MON_ERROR);
            cerr << "Month must be between 1 and 12\n";
        }
        else if (m_day < 1 || m_day > mdays()) {
            errCode(DAY_ERROR);
            cerr << "Day must be between 1 and " << mdays() << endl;
        }    
        return !bad();                  // return true or false.
    }

    // Function to get the number of days in a month
    int Date::mdays() const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
    }

    // Function to get the system year
    int Date::systemYear() const {
        int theYear = sdds_year;
        if (!sdds_test) {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            theYear = lt.tm_year + 1900;
        }
        return theYear;
    }

    // Function to set the date to today's date
    void Date::setToToday() {
        if (sdds_test) {
            m_day = sdds_day;
            m_mon = sdds_mon;
            m_year = sdds_year;
        }
        else {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            m_day = lt.tm_mday;
            m_mon = lt.tm_mon + 1;  // month + 1
            m_year = lt.tm_year + 1900;  // year + 1900
        }
        errCode(NO_ERROR);
    }

    // Function to get the number of days since 0001-01-01
    int Date::daysSince0001_1_1() const {
        int year = m_year;
        int month = m_mon;
        if (month < 3) {
            year--;
            month += 12;
        }
        return 365 * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + m_day - 306;
    }

    // Getter function for days since 0001-01-01
    int Date::daysSince0001_1_1_getter() const {
        return daysSince0001_1_1();
    }

    // Default constructor for Date class
    Date::Date() : m_CUR_YEAR(systemYear()) {
        setToToday();
    }

    // Parameterized constructor for Date class
    Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear()) {
        m_year = year;
        m_mon = mon;
        m_day = day;
        validate();
    }

    // Function to get the status of the date
    const char* Date::dateStatus() const {
        return DATE_ERROR[errCode()];
    }

    // Function to get the current year
    int Date::currentYear() const {
        return m_CUR_YEAR;
    }

    // Function to set the error code
    void Date::errCode(int readErrorCode) {
        m_ErrorCode = readErrorCode;
    }

    // Function to get the error code
    int Date::errCode() const {
        return m_ErrorCode;
    }

    // Function to check if the date is valid
    bool Date::bad() const {
        return m_ErrorCode != 0;
    }

    // Input function for Date class
    istream& Date::read(istream& istr) {
        errCode(NO_ERROR);

        istr >> m_year;
        istr.ignore();
        istr >> m_mon;
        istr.ignore();
        istr >> m_day;
        
        if (!istr) {
            errCode(CIN_FAILED);
        }
        else {
            validate();                     // returns true or false
        }

        return istr;
    }

    // Output function for Date class
    ostream& Date::write(ostream& ostr) const {
        if (bad()) {
            ostr << dateStatus();
        }
        else {
            ostr << m_year << "/"
                << setw(2) << right << setfill('0') << m_mon << "/"
                << setw(2) << right << setfill('0') << m_day;
        }
        return ostr;
    }

    //-----------------------------------------------------------------------------------------

    // Friend function to overload the >> operator for Date class
    istream& operator>>(istream& istr, Date& RO) {
        return RO.read(istr);
    }

    // Friend function to overload the << operator for Date class
    ostream& operator<<(ostream& ostr, const Date& RO) {
        return RO.write(ostr);
    }

    // Comparison operators for Date class
    bool operator>=(const Date& ob1, const Date& ob2) {
        return (ob1.daysSince0001_1_1_getter() >= ob2.daysSince0001_1_1_getter());
    }

    bool operator<=(const Date& ob1, const Date& ob2) {
        return (ob1.daysSince0001_1_1_getter() <= ob2.daysSince0001_1_1_getter());
    }

    bool operator<(const Date& ob1, const Date& ob2) {
        return ob1.daysSince0001_1_1_getter() < ob2.daysSince0001_1_1_getter();
    }

    bool operator>(const Date& ob1, const Date& ob2) {
        return ob1.daysSince0001_1_1_getter() > ob2.daysSince0001_1_1_getter();
    }

    // Subtraction operator for Date class
    int operator-(const Date& ob1, const Date& ob2) {
        return (ob1.daysSince0001_1_1_getter() - ob2.daysSince0001_1_1_getter());
    }

    //-----------------------------------------------------------------------------------------

    // Conversion operator to bool for Date class
    Date::operator bool() const {
        return (!bad());
    }

    // Equality operator for Date class
    bool Date::operator==(const Date& ob2) const {
        return (daysSince0001_1_1() == ob2.daysSince0001_1_1());
    }

    // Inequality operator for Date class
    bool Date::operator!=(const Date& ob2) const {
        return (daysSince0001_1_1() != ob2.daysSince0001_1_1());
    }
}
