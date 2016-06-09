#include "sources/subscriber/Subscriber.hpp"

int main()
{
    Subscriber subscriber("127.0.0.1");
    subscriber.start("", "AAAA");

    return 0;
}
