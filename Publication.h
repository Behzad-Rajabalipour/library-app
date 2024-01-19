// Header guard to prevent multiple inclusions of the same header file
#ifndef SDDS_PUBLICATION_H_
#define SDDS_PUBLICATION_H_

#include <iostream>
#include <cstring>
#include "Lib.h"  // Include necessary header file(s)
#include "Streamable.h"  // Include necessary header file(s)
#include "Date.h"  // Include necessary header file(s)

using namespace std;

namespace sdds {
    // Class representing a Publication, derived from Streamable
    class Publication : public Streamable {
        char* m_title;  // Pointer to a character array representing the title
        char m_shelfId[SDDS_SHELF_ID_LEN + 1];  // Character array representing the shelf ID
        int m_membership;  // Integer representing membership information
        int m_libRef;  // Integer representing library reference
        Date m_date;  // Date object representing the date of the publication

    public:
        // Constructors and destructor
        Publication();  // Default constructor
        Publication(const Publication&);  // Copy constructor
        Publication& operator=(const Publication&);  // Copy assignment operator
        ~Publication();  // Destructor

        // Member functions
        virtual void set(int);  // Virtual function to set membership information
        virtual char type() const;  // Virtual function to get the type of the publication
        bool conIO(ios&) const;  // Function to check if the publication is in console I/O mode
        int getRef() const;  // Function to get the library reference
        void setRef(int);  // Function to set the library reference
        void resetDate();  // Function to reset the date
        void setDefault();  // Function to set default values
        bool onLoan() const;  // Function to check if the publication is on loan
        Date checkoutDate() const;  // Function to get the checkout date
        bool operator==(const char*) const;  // Equality comparison operator with a character array
        operator bool() const;  // Conversion operator to bool
        operator const char* () const;  // Conversion operator to a constant character array

        // Streamable interface functions
        ostream& write(ostream & = cout) const;  // Function to write the publication data to an output stream
        istream& read(istream & = cin);  // Function to read the publication data from an input stream
    };
}

// End of header guard
#endif // !SDDS_PUBLICATION_H_
