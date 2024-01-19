// Header guard to prevent multiple inclusions of the same header file
#ifndef SDDS_MENU_H
#define SDDS_MENU_H

#include <iostream>

namespace sdds {
    // Constant representing the maximum number of menu items
    const unsigned MAX_MENU_ITEMS = 20;

    // Class representing a MenuItem
    class MenuItem {
        char* m_content;  // Pointer to a character array representing the content of the menu item

        // Private member functions
        MenuItem();  // Private default constructor
        MenuItem(const char*);  // Private constructor with a character array parameter
        ~MenuItem();  // Private destructor
        void setEmpty();  // Private function to set the menu item to an empty state
        bool isValid(const char*) const;  // Private function to check if the given content is valid
        bool isValid() const;  // Private function to check if the menu item is valid

        // Conversion operators
        operator bool() const;  // Conversion operator to bool
        operator char* () const;  // Conversion operator to a constant character array
        std::ostream& display(std::ostream & = std::cout) const;  // Function to display the menu item content

        // Friend class Menu to allow access to private members
        friend class Menu;
    };

    // Class representing a Menu
    class Menu {
        MenuItem menuItem_title;  // MenuItem representing the title of the menu
        MenuItem* menuItems[MAX_MENU_ITEMS];  // Array of pointers to MenuItem representing the menu items

        unsigned Counter;  // Counter representing the number of menu items
        void setEmpty();  // Private function to set the menu to an empty state

    public:
        // Constructors and destructor
        Menu();  // Default constructor
        Menu(const char*);  // Constructor with a character array parameter
        ~Menu();  // Destructor

        // Deleted copy constructor and copy assignment operator
        Menu(const Menu& M) = delete;  // Copy constructor is not allowed
        void operator=(const Menu& M) = delete;  // Copy assignment is not allowed

        // Conversion operators
        operator int();  // Conversion operator to int
        operator unsigned int();  // Conversion operator to unsigned int
        operator bool();  // Conversion operator to bool
        char* operator [](unsigned int) const;  // Subscript operator to get menu item content
        int operator~();  // Bitwise NOT operator to get the number of menu items

        // Member functions
        std::ostream& displayMenuTitle(std::ostream & = std::cout) const;  // Function to display the menu title
        std::ostream& displayMenu(std::ostream & = std::cout) const;  // Function to display the entire menu
        int run();  // Function to run the menu

        // Operator overloads for adding menu items
        Menu& operator<<(const char*);  // Left-shift operator to add a menu item

        // Friend function to allow operator<< to access private members
        friend std::ostream& operator<<(std::ostream&, Menu&);
    };

    // Operator overload for displaying the menu using cout
    std::ostream& operator<<(std::ostream&, Menu&);
}

// End of header guard
#endif // !SDDS_MENU_H
