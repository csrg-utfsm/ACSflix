#include "sources/publisher/Publisher.hpp"

int main()
{
    Publisher publisher("*");

    publisher.set_block_size(11);
    publisher.set_interval(500);

    publisher.start("test.txt", "AAAA");

    return 0;
}
