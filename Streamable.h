#ifndef SDDS_STREAMABLE_H_
#define SDDS_STREAMABLE_H_

using namespace std;

namespace sdds {
    // Abstract base class for streamable objects
    class Streamable {
    public:
        // Pure virtual function to write to an output stream
        virtual ostream& write(ostream & = cout) const = 0;  // "esmesh" => pure virtual function
        // Pure virtual function to read from an input stream
        virtual istream& read(istream & = cin) = 0;  // Because we have pure virtual functions, instances of this class cannot be created directly; only pointers can. Correct usage: Streamable* p; Error: Streamable ob1;
        // Pure virtual function to check if the object can interact with console I/O
        virtual bool conIO(ios&) const = 0;
        // Conversion operator to bool, indicating if the object is in a valid state
        virtual operator bool() const = 0;
        // Virtual destructor for proper cleanup in derived classes
        virtual ~Streamable() {};
    };

    // Forward declaration of operator overloads for stream insertion and extraction
    // Not implemented here as it depends on the specific derived classes
    ostream& operator<<(ostream&, const Streamable&);
    istream& operator>>(istream&, Streamable&);
}

#endif // !SDDS_STREAMABLE_H_
