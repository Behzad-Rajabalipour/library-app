#include <iostream>
#include "Streamable.h"

using namespace std;

namespace sdds {
    // Overloaded insertion operator for Streamable objects
    ostream& operator<<(ostream& ostr, const Streamable& ob1) {
        if (ob1) {
            ob1.write(ostr);
        }
        return ostr;
    }

    // Overloaded extraction operator for Streamable objects
    istream& operator>>(istream& istr, Streamable& ob1) {
        return (ob1.read(istr));
    }
}  // namespace sdds
