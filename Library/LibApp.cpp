#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "iomanip"
#include "Menu.h"
#include "Book.h"
#include "PublicationSelector.h"
#include "Utils.h"
#include "LibApp.h"

using namespace std;

namespace sdds {
    // Default constructor for LibApp
    LibApp::LibApp() {
        // Initialize main menu and exit menu
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";

        // Load data from file
        load();
    }

    // Parameterized constructor for LibApp with filename
    LibApp::LibApp(const char filename[256]) {
        // Initialize main menu, exit menu, publication menu, and set filename
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_publicationMenu << "Book" << "Publication";
        strcpy(m_filename, filename);

        // Load data from file
        load();
    }

    // Destructor for LibApp
    LibApp::~LibApp() {
        // Deallocate memory for all pointers in PPA array
        for (int i = 0; i < NOLP; i++)
            delete PPA[i];
    }

    // Function to display a confirmation message and get user input
    bool LibApp::confirm(const char* message) {
        // Create a menu with the confirmation message
        Menu obj(message);
        // Add "Yes" option to the menu
        obj << "Yes";
        // Run the menu and get the user input
        int number = obj.run();
        // Return true if user input is not zero
        return (!!number);
    }

    // Function to load data from a file
    void LibApp::load() {
        cout << "Loading Data\n";
        ifstream infile(m_filename);

        // Read data from the file and create Publication objects
        while (infile) {
            char type = {};
            infile >> type;
            infile.ignore();  // Ignore spaces
            if (infile) {
                if (type == 'P')
                    PPA[NOLP] = new Publication;  // Create a Publication object
                else if (type == 'B')
                    PPA[NOLP] = new Book();  // Create a Book object
                else
                    cout << "no data\n";

                // Read data into the Publication object
                PPA[NOLP] && infile >> *PPA[NOLP++];
            }
        }
        // Set LLRN to the reference of the last item
        LLRN = PPA[NOLP - 1]->getRef();
    }

    // Function to save data to a file
    void LibApp::save() {
        cout << "Saving Data\n";
        ofstream fwrite(m_filename);

        // Write data to the file for each Publication
        for (int i = 0; i < NOLP; i++) {
            if (PPA[i]->getRef() != 0)
                fwrite << *PPA[i] << endl;
        }
    }

    // Function to print information about a specific Publication
    void LibApp::prnPub(Publication* p[], int size, int ref) {
        for (int i = 0; i < size; i++) {
            if (ref == p[i]->getRef()) {
                cout << *p[i] << endl;
                break;
            }
        }
    }

    // Function to search for a Publication based on title, type, and loan status
    int LibApp::search(int option, char type) {
        // Create a PublicationSelector object with a message and maximum items
        PublicationSelector ps_obj("Select one of the following found matches:", 15);
        cout << "Publication Title: ";
        char title[256];
        cin.getline(title, 256);

        // Search based on the specified option, type, and title
        if (option == 1) {
            for (int i = 0; i < NOLP; i++) {
                if (strstr(*PPA[i], title) && PPA[i]->getRef() != 0 && type == PPA[i]->type()) {
                    // Add Publication to the PublicationSelector
                    ps_obj << PPA[i];
                }
            }
        }
        else if (option == 2) {
            for (int i = 0; i < NOLP; i++) {
                if (strstr(*PPA[i], title) && !PPA[i]->onLoan() && PPA[i]->getRef() != 0 && type == PPA[i]->type()) {
                    // Add Publication to the PublicationSelector
                    ps_obj << PPA[i];
                }
            }
        }
        else if (option == 3) {
            for (int i = 0; i < NOLP; i++) {
                if (strstr(*PPA[i], title) && PPA[i]->onLoan() && PPA[i]->getRef() != 0 && type == PPA[i]->type()) {
                    // Add Publication to the PublicationSelector
                    ps_obj << PPA[i];
                }
            }
        }

        int reference = 0;
        // Display the PublicationSelector options
        if (ps_obj) {
            ps_obj.sort();
            reference = ps_obj.run();
            // Print information about the selected publication
            if (reference) {
                prnPub(PPA, NOLP, reference);
            }
            else {
                cout << "Aborted!\n";
            }
        }
        else {
            cout << "No matches found!" << endl;
        }
        return reference;
    }

    // Function to process the return of a publication
    void LibApp::returnPub() {
        cout << "Return publication to the library" << endl;
        int selected_type = m_publicationMenu.run();
        char type{};

        // Set the type based on user input
        (selected_type == 1) ? type = 'B' : type = 'P';
        // Search for a publication to return
        int ref_pub = search(3, type);

        if (ref_pub != 0 && confirm("Return Publication?")) {
            // Retrieve the checkout date and calculate the penalty if any
            Date returnDate = getPub(ref_pub)->checkoutDate();
            Date today;  // Default today
            int days = today - returnDate;
            days -= 15;  // 15 days grace period, add penalty if overdue

            if (days > 0) {
                cout << fixed << setprecision(2) << "Please pay $" << float(days) * (0.5)
                    << " penalty for being " << days << " days late!\n";
            }
            // Set the publication status to available
            getPub(ref_pub)->set(0);
            cout << "Publication returned\n";
            m_changed = true;
        }
    }

    // Function to add a new publication to the library
    void LibApp::newPublication() {
        if (NOLP >= SDDS_LIBRARY_CAPACITY) {
            cout << "Library is at its maximum capacity!\n";
            return;
        }
        cout << "Adding new publication to the library\n";
        // Get user input for the type of publication
        int input_number = m_publicationMenu.run();
        Publication* ptr = nullptr;
        if (input_number == 0) {
            cout << "Aborted!\n";
            return;
        }
        else if (input_number == 1) {
            ptr = new Book;  // Create a Book object
            cin >> *ptr;     // Input data for the Book
        }
        else if (input_number == 2) {
            ptr = new Publication;  // Create a Publication object
            cin >> *ptr;            // Input data for the Publication
        }
        if (!cin) {
            cout << "\nAborted!\n";
            exit(0);
        }

        // Confirm and add the new publication to the library
        if (confirm("Add this publication to the library?")) {
            ptr->setRef(++LLRN);  // Increment and set reference
            PPA[NOLP++] = ptr;    // Add pointer to the array
            m_changed = true;
            cout << "Publication added\n";
        }
        if (!*ptr) {
            cout << "Failed to add publication!\n";
            delete ptr;
        }
    }

    // Function to retrieve a Publication object based on its reference
    Publication* LibApp::getPub(int libRef) {
        for (int i = 0; i < NOLP; i++)
            if (libRef == PPA[i]->getRef()) return PPA[i];
        return nullptr;
    }

    // Main function to process the removal of a publication from the library
    void LibApp::removePublication() {
        cout << "Removing publication from the library\n";

        // Get user input for the type of publication
        int number = m_publicationMenu.run();
        char type;

        // Set the type based on user input
        if (number == 1 || number == 2) {
            if (number == 1) type = 'B';
            else if (number == 2) type = 'P';
            // Search for a publication to remove
            int reference = search(1, type);
            if (reference != 0 && confirm("Remove this publication from the library?")) {
                m_changed = true;
                getPub(reference)->setRef(0);  // Set reference to 0 to mark as removed
                cout << "Publication removed\n";
            }
        }
    }

    // Main function to process checking out a publication
    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library\n";
        // Get user input for the type of publication
        int input = m_publicationMenu.run();
        char type;

        // Set the type based on user input
        if (input == 1) type = 'B';
        else type = 'P';

        // Search for a publication to check out
        int reference = search(2, type);
        if (reference != 0 && confirm("Check out publication?")) {
            m_changed = true;
            int membership_num;
            cout << "Enter Membership number (between 9999 and 99999): ";
            while (1) {
                cin >> membership_num;
                // Validate the membership number
                if (membership_num > 9999 && membership_num <= 99999) break;
                cout << "Invalid membership number, try again: ";
            }
            // Set the publication status and checkout date
            getPub(reference)->set(membership_num);
            cout << "Publication checked out\n";
        }
    }

    // Main function to run the library application
    void LibApp::run() {
        while (1) {
            int input = m_mainMenu.run();
            if (input == 1) {
                newPublication();
            }
            else if (input == 2) {
                removePublication();
            }
            else if (input == 3) {
                checkOutPub();
            }
            else if (input == 4) {
                returnPub();
            }
            else if (input == 0) {
                // Check for changes before exiting
                if (m_changed) {
                    int num = m_exitMenu.run();
                    if (num == 1) {
                        save();
                        break;
                    }
                    else if (num == 2) {
                        // Do nothing and go back to the main menu
                    }
                    else if (num == 0) {
                        // Confirm discarding changes before exiting
                        if (confirm("This will discard all the changes, are you sure?"))
                            break;
                    }
                    else
                        break;
                }
                else {
                    break;
                }

            }
            cout << endl;
        }
        cout << endl;
        cout << "-------------------------------------------\n"
            << "Thanks for using Seneca Library Application\n";
    }

}  // namespace sdds
