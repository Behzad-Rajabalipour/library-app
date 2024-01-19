// Header guard to prevent multiple inclusions of the same header file
#ifndef SDDS_PUBLICATIONSELECTOR_H
#define SDDS_PUBLICATIONSELECTOR_H

#include "Publication.h"  // Include necessary header file(s)

namespace sdds {
    // A class representing a publication selector
    class PublicationSelector {
        const int allocationUnit{ 10 };  // Constant representing the allocation unit for dynamic memory
        const int m_pageSize{};  // Constant representing the page size (initialized in the constructor)
        const Publication** m_pub{};  // Pointer to an array of pointers to Publication objects
        char m_title[81]{};  // Character array to store the title of the selector
        int m_currentPage{ 1 };  // Integer representing the current page of the selector
        int m_arraySize{};  // Integer representing the size of the array of pointers
        int m_noOfPubs{};  // Integer representing the number of publications in the selector

        // Private member functions
        void display(int page) const;  // Display function to show publications on a specified page
        int getSelectedLibRef() const;  // Get the library reference of the selected publication

    public:
        // Constructor with default values for parameters
        PublicationSelector(const char* title = "Select a publication: ", int pageSize = 15);

        // Destructor to release dynamically allocated memory
        ~PublicationSelector();

        // Deleted copy constructor and copy assignment operator to prevent copying
        PublicationSelector(const PublicationSelector&) = delete;
        PublicationSelector& operator=(const PublicationSelector&) = delete;

        // Overloaded operators to add publications to the selector
        PublicationSelector& operator<<(const Publication* pub);  // Add publication by address
        PublicationSelector& operator<<(const Publication& pub);  // Add publication by reference

        // Conversion operator to bool, indicating if the selector is not empty
        operator bool() const;

        // Function to reset the selector, clearing all publications and making it ready to be refilled
        void reset();

        // Function to sort the publications based on date and title
        void sort();

        // Function to run the selector, returning the library reference of the selected publication
        int run();
    };
}

// End of header guard
#endif // !SDDS_PUBLICATIONSELECTOR_H
