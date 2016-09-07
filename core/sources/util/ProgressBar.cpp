#include "ProgressBar.hpp"

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

ProgressBar::ProgressBar(size_t total) :
        total(total), cursor(0), width(100)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col - (size_t) 15;
}

bool ProgressBar::is_tty()
{
    return !isatty(fileno(stdin));
}

void ProgressBar::render()
{
    if (is_tty()) {
        // abort if this is not a tty.
        return;
    }

    float progress = cursor / (float) total;
    int pos = (int) (width * progress);

    std::cout << "[";
    for (int i = 0; i < width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }

    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

void ProgressBar::set_cursor(size_t cursor)
{
    this->cursor = cursor;
    render();
}
