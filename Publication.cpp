#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Publication.h"
#include "iomanip"
#include <cctype> 

using namespace std;

namespace sdds {
    // Default constructor for Publication
    Publication::Publication() {
        setDefault();
    }

    // Destructor for Publication
    Publication::~Publication() {
        delete[] m_title;
    }

    // Copy constructor for Publication
    Publication::Publication(const Publication& ob1) {
        *this = ob1;
    }

    // Copy assignment operator for Publication
    Publication& Publication::operator=(const Publication& ob1) {
        // Copy member variables from ob1 to *this
        set(ob1.m_membership);
        setRef(ob1.m_libRef);
        strcpy(m_shelfId, ob1.m_shelfId);
        m_date = ob1.m_date;

        // Delete existing m_title memory
        if (m_title) {
            delete[] m_title;
            m_title = nullptr;
        }

        // Copy m_title from ob1 if it is not nullptr
        if (ob1.m_title != nullptr) {
            m_title = new char[strlen(ob1.m_title) + 1];
            strcpy(m_title, ob1.m_title);
        }
        else {
            m_title = nullptr;
        }
        return *this;
    }

    // Function to set default values for Publication
    void Publication::setDefault() {
        m_title = nullptr;
m_shelfId[0] = '\0';
m_membership = 0;
m_libRef = -1;
resetDate();
    }

    // Function to set membership for Publication
    void Publication::set(int member_id) {
        m_membership = member_id;
    }

    // Function to set reference for Publication
    void Publication::setRef(int value) {
        m_libRef = value;
    }

    // Function to reset the date for Publication
    void Publication::resetDate() {
        m_date = Date();
    }

    // Function to return the type of Publication
    char Publication::type() const {
        return 'P';
    }

    // Function to check if a Publication is on loan
    bool Publication::onLoan() const {
        return (m_membership != 0);
    }

    // Function to return the checkout date of a Publication
    Date Publication::checkoutDate() const {
        return m_date;
    }

    // Function to check if the input/output stream is console-based
    bool Publication::conIO(ios& io) const {
        return &io == &cin || &io == &cout;
    }

    // Overloaded equality operator to compare a Publication's title with a given title
    bool Publication::operator==(const char* title) const {
        return strstr(m_title, title) != nullptr;
    }

    // Conversion operator to bool for Publication
    Publication::operator bool() const {
        return (m_title != nullptr && m_shelfId[0] != '\0');
    }

    // Conversion operator to const char* for Publication
    Publication::operator const char* () const {
        return m_title;
    }

    // Function to get the reference of a Publication
    int Publication::getRef() const {
        return m_libRef;
    }

    // Function to write the Publication information to the output stream
    ostream& Publication::write(ostream& os) const {
        char t_title[SDDS_TITLE_WIDTH + 1] = { 0 };
        strncpy(t_title, m_title, SDDS_TITLE_WIDTH);
        if (conIO(os)) {
            // Output information for console-based stream
            os << "| " << m_shelfId << " | "
                << setw(30) << left << setfill('.')
                << t_title << " | ";
            (m_membership != 0) ? os << m_membership : os << " N/A ";
            os << " | " << m_date << " |";
        }
        else {
            // Output information for file-based stream
            os << type();
            os << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";
            (m_membership != 0) ? os << m_membership : os << "0";
            os << "\t" << m_date;
        }
        return os;
    }

    // Function to read the Publication information from the input stream
    istream& Publication::read(istream& is) {
        // Reset to default values
        if (m_title) {
            delete[] m_title;
            m_title = nullptr;
        }
        setDefault();
        m_title = new char[1000];

        if (conIO(is)) {
            // Read input from console
            char temp[1000];
            while (true) {
                cout << "Shelf No: ";
                is.getline(temp, 1000, '\n');

                // Check if the first character is an alphabet and the next three are digits
                if (isalpha(temp[0]) && isdigit(temp[1]) && isdigit(temp[2]) && isdigit(temp[3]) && temp[4] == '\0') {
                    strncpy(m_shelfId, temp, SDDS_SHELF_ID_LEN + 1);  // Valid input
                    break; // Exit the loop if the input is valid
                }
                else {
                    // Invalid input
                    cerr << "Invalid Shelf No format. Please enter again. "
                        << "It must be this Format: [Alphabet][Number][Number][Number]" << endl;
                    is.clear();
                }
            }

            cout << "Title: ";
            cin.getline(m_title, 1000, '\n');
            if (strlen(m_title) > SDDS_TITLE_WIDTH) {
                is.clear();
            }

            cout << "Date: ";
            is >> m_date;   

        }
        else {
            // Read input from file
            is >> m_libRef;
            is.ignore();
            is.getline(m_shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
            is.getline(m_title, 1000, '\t');
            is >> m_membership;
            is.ignore();
            is >> m_date;
        }

        while (!m_date) {                       // Ask client untill he input correct Date
            cout << "Date: ";
            is >> m_date;
            // is.setstate(ios::failbit);       // This is for failbit, if use this one then we will get Aborted!
            // m_date = Date(2023, 07, 11);     // default m_date
        }

        return is;
    }

}  // namespace sdds
