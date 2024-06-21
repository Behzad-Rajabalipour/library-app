# Library App

This repository contains a library management application developed using C++. The application supports managing book records, user interactions, and various library functionalities.
## Main Functions:
•	Added, removed, and updated publications, books, articles, and authors. <br/>
•	Implemented check-in and check-out features for each client ID. <br/>
•	Developed sorting functionality based on publication date, author, publication name, number of reviews, and more. <br/>

	 C++ - Code Review – Problem Solving – Debugging – Object-Oriented Programming (OPP) 

## Table of Contents
- [About](#about)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [Folder Structure](#folder-structure)
- [Contributing](#contributing)
- [License](#license)

## About
The Library App is a console-based application designed to manage library operations such as adding, removing, and updating book records, managing user interactions, and providing an organized way to handle library data.

## Features
- Add, update, and remove book records
- View a list of available books
- Search for books by title or author
- Manage user interactions with the library system
- Load and save library data to files

## Technologies Used
- **C++**: The core programming language used for the application
- **File I/O**: For saving and loading data
- **Object-Oriented Programming**: For organizing code into classes and objects

## Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/Behzad-Rajabalipour/library-app.git
    cd library-app
    ```

2. **Open the project in your preferred C++ IDE or text editor.**

3. **Build the project:**
    - If you are using an IDE like Visual Studio, open the project file (`.vcxproj`) and build the solution.
    - If you are using a text editor and command line, use a C++ compiler to compile the code:
    ```bash
    g++ -o library-app *.cpp
    ```

4. **Run the application:**
    ```bash
    ./library-app
    ```

## Usage
- Follow the on-screen prompts to navigate through the library management options.
- Use the menu to add, update, remove, and search for books.
- The application will save the changes to the files upon exit.

## Folder Structure
- `x64/Debug/`: Contains debug builds.
- `Books.txt`: File containing book records.
- `BooksOriginal.txt`: Original book records.
- `Date.cpp` and `Date.h`: Date handling classes.
- `Lib.h`: Library header file.
- `LibApp.cpp` and `LibApp.h`: Main library application files.
- `LibAppMain.cpp` and `LibAppMain_prof.cpp`: Entry points for the application.
- `LibRecs.txt` and `LibRecsSmall.txt`: Library records.
- `Menu.cpp` and `Menu.h`: Menu handling classes.
- `Publication.cpp` and `Publication.h`: Publication handling classes.
- `PublicationSelector.cpp` and `PublicationSelector.h`: Publication selection classes.
- `Streamable.cpp` and `Streamable.h`: Streamable interface classes.
- `Utils.cpp` and `Utils.h`: Utility functions.

## Contributing
Contributions are welcome! Please open an issue or submit a pull request for any bugs or feature requests.

### Steps to Contribute:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

## License
This project is done by Behzad Rajabalipour.
