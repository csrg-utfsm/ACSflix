#ifndef PUBLISHER_PROGRESSBAR_HPP
#define PUBLISHER_PROGRESSBAR_HPP

#include <cstddef>

class ProgressBar
{
private:
    size_t total;
    size_t cursor;
    size_t width;

    void render();

public:
    ProgressBar(size_t total);

    void set_cursor(size_t cursor);

    bool is_tty();
};


#endif //PUBLISHER_PROGRESSBAR_HPP
