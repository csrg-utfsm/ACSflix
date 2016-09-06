#include "utils.h"

int bdt::str_to_int(std::string value)
{
    int i;
    std::istringstream is(value);
    is >> i;
    return i;
}

std::string bdt::size_to_str(size_t value)
{
    std::ostringstream is;
    is << value;
    return is.str();
}
