// Header guard to prevent multiple inclusions of the same header file
#ifndef SDDS_BOOK_H_
#define SDDS_BOOK_H_

#include "Publication.h"

namespace sdds {
    // Book class declaration, derived from Publication
    class Book : public Publication {
        char* authorName;  // Pointer to the author's name

    public:
        // Constructors and destructor
        Book();                           // Default constructor
        Book(const Book&);                // Copy constructor
        Book& operator=(const Book&);     // Copy assignment operator (output data)
        ~Book();                          // Destructor

        // Member functions
        void setBookEmpty();              // Sets the book to an empty state
        char type() const;                // Returns the type of the publication ('B' for Book)
        void set(int);                    // Sets the book's data
        operator bool() const;            // Conversion operator to bool

        // Input and output functions
        ostream& write(ostream&) const;   // Outputs the book's information
        istream& read(istream&);          // Reads the book's information from input
    };
}

// End of header guard
#endif // !SDDS_BOOK_H_
