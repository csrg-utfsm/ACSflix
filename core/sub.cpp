#include "sources/subscriber/Subscriber.hpp"

int main()
{
    Subscriber subscriber("127.0.0.1");
    // subscriber.set_interval(100);
    subscriber.start("copy.mp4", "AAAA");

    return 0;
}
