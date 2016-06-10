#ifndef PUBLISHER_SUBSCRIBER_HPP
#define PUBLISHER_SUBSCRIBER_HPP

#include <czmq.h>
#include <memory>
#include "../DataEndPoint.hpp"
#include <vector>


class Subscriber : public DataEndPoint
{
private:
    void consume(FILE *message, std::unique_ptr<_zmsg_t, void (*)(_zmsg_t *)>::pointer pZmsg);

    auto deleter = [](zmsg_t * message) {
        zmsg_destroy(&message);
    };

public:
    Subscriber(std::string ip);

    void subscribe(std::string channel);

    void start(std::string file_path, std::string channel);
};


#endif //PUBLISHER_SUBSCRIBER_HPP
