#ifndef PUBLISHER_UTILS_H
#define PUBLISHER_UTILS_H

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

}; // Bulk Data Transfer


#endif //PUBLISHER_UTILS_H
