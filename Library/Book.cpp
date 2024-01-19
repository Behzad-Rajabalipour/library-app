// Include necessary headers
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Book.h"
#include <cstring>
#include "iomanip"

using namespace std;

namespace sdds {
    // Default constructor for Book class
    Book::Book() {
        setBookEmpty();
    }

    // Copy constructor for Book class
    Book::Book(const Book& ob1) : Publication(ob1) {
        // Copy the authorName from the source object to the current object
        if (authorName) {
            delete[] authorName;
            authorName = nullptr;
        }
        authorName = new char[strlen(ob1.authorName) + 1];
        strcpy(authorName, ob1.authorName);
    }

    // Copy assignment operator for Book class
    Book& Book::operator=(const Book& book) {
        // Invoke the copy assignment of the base class (Publication)
        Publication::operator=(book);

        // Delete the existing authorName and copy the new one
        if (authorName) {
            delete[] authorName;
            authorName = nullptr;
        }
        if (book.authorName) {
            authorName = new char[strlen(book.authorName) + 1];
            strcpy(authorName, book.authorName);
        }
        return *this;
    }

    // Destructor for Book class
    Book::~Book() {
        delete[] authorName;
    }

    // Write function to output Book information
    ostream& Book::write(ostream& os) const {
        // Invoke the write function of the base class (Publication)
        Publication::write(os);

        if (Publication::conIO(os)) {  // Output to console
            char author[SDDS_AUTHOR_WIDTH + 1]{ 0 };
            strncpy(author, authorName, SDDS_AUTHOR_WIDTH);
            os << " ";
            os << setw(SDDS_AUTHOR_WIDTH) << left << setfill(' ') << author << " |";
        }
        else {  // Output to file
            os << "\t" << authorName;
        }
        return os;
    }

    // Read function to input Book information
    istream& Book::read(istream& is) {
        // Invoke the read function of the base class (Publication)
        Publication::read(is);

        char author[256] = { 0 };

        // Delete existing authorName
        if (authorName) {
            delete[] authorName;
            authorName = nullptr;
        }

        if (Publication::conIO(is)) {  // Input from console
            is.ignore();
            cout << "Author: ";
        }
        else {  // Input from file
            is.ignore(1000, '\t');
        }

        // Read the author's name
        is.get(author, 256);

        if (is) {
            // Allocate memory for authorName and copy the author's name
            authorName = new char[strlen(author) + 1];
            strcpy(authorName, author);
        }

        return is;
    }

    // Return the type of the publication (Book)
    char Book::type() const {
        return 'B';
    }

    // Set the Book to an empty state
    void Book::setBookEmpty() {
        authorName = nullptr;
    }

    // Set function to initialize Book object
    void Book::set(int member_id) {
        // Invoke set and resetDate functions of the base class (Publication)
        Publication::set(member_id);
        Publication::resetDate();
    }

    // Conversion operator to bool
    Book::operator bool() const {
        // Return true if authorName is not null and the base class is valid
        return authorName && Publication::operator bool();
    }
}
