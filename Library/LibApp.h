// Header guard to prevent multiple inclusions of the same header file
#ifndef SDDS_LIPAPP_H_
#define SDDS_LIPAPP_H_

#include <cstring>
#include "Menu.h"
#include "Publication.h"
#include "Lib.h"

namespace sdds {
    // Class representing the Library Application
    class LibApp {
        char m_filename[256]{};  // Array of characters representing the filename
        Publication* PPA[SDDS_LIBRARY_CAPACITY]{};  // Array of pointers to Publication representing the publications
        int NOLP = 0;  // Number of loaned publications
        int LLRN = 0;  // Library reference number
        bool m_changed = false;  // Boolean indicating whether changes have been made

        // Menus used in the Library Application
        Menu m_publicationMenu{ "Choose the type of publication:" };  // Menu for choosing the type of publication
        Menu m_mainMenu{ "Seneca Library Application" };  // Main menu of the Library Application
        Menu m_exitMenu{ "Changes have been made to the data, what would you like to do?" };  // Menu for handling changes

        // Private member functions
        bool confirm(const char*);  // Function to confirm an action
        void load();  // Function to load data from a file
        void save();  // Function to save data to a file
        int search(int, char);  // Function to search for a publication
        void returnPub();  // Function to return a publication
        void newPublication();  // Function to add a new publication
        void prnPub(Publication* [], int, int);  // Function to print publications
        void removePublication();  // Function to remove a publication
        void checkOutPub();  // Function to check out a publication
        Publication* getPub(int);  // Function to get a publication by library reference

    public:
        // Constructors and destructor
        LibApp();  // Default constructor
        LibApp(const char[256]);  // Constructor with a character array parameter
        ~LibApp();  // Destructor

        // Member function to run the Library Application
        void run();
    };
}

// End of header guard
#endif // SDDS_LIPAPP_H_
