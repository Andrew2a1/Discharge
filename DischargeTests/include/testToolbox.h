#include <ostream>
#include "../../toolbox/vector.h"

template <typename T>
std::ostream& operator << ( std::ostream& os, Vector<T> const& value ) {
    os << "{";
    for(int i = 0; i < value.size(); ++i)
    {
        os << value[i] << ", ";
    }
    os << "}";
    return os;
}