#include "sources/publisher/Publisher.hpp"

int main()
{
    Publisher publisher("*");

    publisher.set_block_size(1024);
    publisher.set_interval(1);

    publisher.start("test.mp4", "AAAA");

    return 0;
}
