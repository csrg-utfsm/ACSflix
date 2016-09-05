#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

namespace bdt
{
    int str_to_int(std::string value)
    {
        int i;
        std::istringstream is(value);
        is >> i;
        return i;
    }

    std::string size_to_str(size_t value)
    {
        std::ostringstream is;
        is << value;
        return is.str();
    }
}; // Bulk Data Transfer

#endif //UTILS_H
