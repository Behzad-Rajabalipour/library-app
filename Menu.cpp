#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include "Utils.h"
#include "string.h"
#include "iomanip"

using namespace std;

namespace sdds {
    // class MenuItem
    MenuItem::MenuItem() {
        setEmpty();
    }

    MenuItem::MenuItem(const char* content) {
        if (isValid(content)) {
            m_content = new char[strlen(content) + 1];
            strcpy(m_content, content);
        }
        else {
            setEmpty();
        }
    }

    void MenuItem::setEmpty() {
        m_content = nullptr;
    }

    bool MenuItem::isValid(const char* content) const {
        return (content && content[0] != '\0');
    }

    bool MenuItem::isValid()const {
        return (m_content && m_content[0] != '\0');
    }

    MenuItem::~MenuItem() {
        delete[] m_content;
    }

    MenuItem::operator bool()const {
        return (m_content && m_content[0] != '\0');
    }

    MenuItem::operator char* () const {
        return m_content;
    }

    ostream& MenuItem::display(ostream& ostr)const {
        if (*this) ostr << m_content;
        return ostr;
    }

    //-------------------------------------------------------------------------
    // class Menu
    Menu::Menu() {
        setEmpty();
    }

    Menu::Menu(const char* title) :menuItem_title(title) {
        setEmpty();
    };

    Menu::~Menu() {
        for (unsigned i = 0; i < MAX_MENU_ITEMS; i++) {
            delete menuItems[i];
        }
    }

    void Menu::setEmpty() {
        for (unsigned i = 0; i < MAX_MENU_ITEMS; i++) {
            menuItems[i] = nullptr;
        }
        *menuItems = nullptr;
        Counter = 0;
    }

    Menu::operator bool() {
        return Counter > 0;
    }

    Menu::operator int() {
        return Counter;
    }

    Menu::operator unsigned int() {
        return Counter;
    }

    int Menu::operator~() {
        return run();
    }

    ostream& Menu::displayMenuTitle(ostream& ostr) const {
        return menuItem_title.display(ostr);
    }

    ostream& Menu::displayMenu(ostream& ostr)const {
        if (menuItem_title) {
            // Display the menu title if it is valid
            menuItem_title.display();
            ostr << endl;
        }

        // Display each menu item along with its index
        for (unsigned i = 0; i < Counter; i++) {
            ostr.width(2);
            ostr.setf(ios::right);
            ostr.fill(' ');
            ostr << i + 1 << "- ";
            ostr.unsetf(ios::right);
            menuItems[i]->display(ostr) << endl;
        }

        // Display the exit option
        ostr << " 0- Exit" << "\n" << "> ";

        return ostr;
    }

    int Menu::run() {
        displayMenu();
        int number = getInteger(0, Counter);
        return number;
    }

    char* Menu::operator[](unsigned int index)const {
        // Ensure the index is within bounds
        while (index > Counter)
            index %= Counter; // Wrap around if necessary

        // Return the content of the selected menu item
        return menuItems[index]->m_content;
    }

    Menu& Menu::operator<<(const char* menuitemContent) {
        if (Counter < MAX_MENU_ITEMS) {
            // Create a new MenuItem and add it to the menu
            MenuItem* newMenuItem = new MenuItem(menuitemContent);
            menuItems[Counter] = nullptr;
            menuItems[Counter] = newMenuItem;
            Counter++;
        }
        return *this;
    }

    // Out of the class
    ostream& operator<<(ostream& ostr, Menu& ob1) {
        // Display the menu title
        return ob1.displayMenuTitle(ostr);
    }

}  // namespace sdds
